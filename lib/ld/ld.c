#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/ipc/ro.h>

#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>
#include<libtransistor/ld/module.h>

#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>

const bool RELOCATION_DEBUG = false; // run under Mephisto with --relocate

static trn_list_head_t module_list_head = TRN_LIST_HEAD_INITIALIZER;
static const char *ld_search_path[] = {
	"/sd/lib/",
	"/squash/lib/",
	"/squash/",
};

typedef struct {
	uint32_t magic, dynamic_off, bss_start_off, bss_end_off;
	uint32_t unwind_start_off, unwind_end_off, module_object_off;
} module_header_t;

static result_t dynamic_find_value(Elf64_Dyn *dynamic, int64_t tag, uint64_t *value);
static result_t dynamic_find_offset(Elf64_Dyn *dynamic, int64_t tag, void **value, void *aslr_base);
result_t ld_basic_relocate_module(uint8_t *module_base);
result_t ld_add_module(module_input_t input, module_t **out);
result_t ld_discover_module(const char *name_src, module_t **out);
result_t ld_decref_module(module_t *mod);
result_t ld_scan_module(module_t *mod);
static uint64_t elf_hash(const uint8_t *name);
result_t ld_find_definition(Elf64_Sym *find, module_t *find_module, Elf64_Sym **def, module_t **defining_module);
result_t ld_run_relocation_table(module_t *mod, uint32_t offset_tag, uint32_t size_tag);
result_t ld_relocate_module(module_t *mod);
result_t ld_process_modules();
result_t ld_finalize_module(module_t *mod);

static result_t dynamic_find_value(Elf64_Dyn *dynamic, int64_t tag, uint64_t *value) {
	uint64_t *found = NULL;
	*value = 0;
	for(; dynamic->d_tag != DT_NULL; dynamic++) {
		if(dynamic->d_tag == tag) {
			if(found != NULL) {
				return LIBTRANSISTOR_ERR_TRNLD_DUPLICATE_DT_ENTRY;
			} else {
				found = &dynamic->d_val;
			}
		}
	}
	if(found == NULL) {
		return LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY;
	}
	*value = *found;
	return RESULT_OK;
}

static result_t dynamic_find_offset(Elf64_Dyn *dynamic, int64_t tag, void **value, void *aslr_base) {
	uint64_t intermediate;
	result_t r = dynamic_find_value(dynamic, tag, &intermediate);
	*value = aslr_base + intermediate;
	return r;
}

result_t ld_basic_relocate_module(uint8_t *module_base) {
	module_header_t *mod_header = (module_header_t *)&module_base[*(uint32_t*) &module_base[4]];
	Elf64_Dyn *dynamic = (Elf64_Dyn*) (((uint8_t*) mod_header) + mod_header->dynamic_off);
	uint64_t rela_offset = 0;
	uint64_t rela_size = 0;
	uint64_t rela_ent = 0;
	uint64_t rela_count = 0;

	const char mod_magic[] = "MOD0";
	if(mod_header->magic != *((uint32_t*) mod_magic)) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_MODULE_HEADER;
	}

	result_t r;
	LIB_ASSERT_OK(fail, dynamic_find_value (dynamic, DT_RELA,      &rela_offset));
	LIB_ASSERT_OK(fail, dynamic_find_value (dynamic, DT_RELASZ,    &rela_size));
	LIB_ASSERT_OK(fail, dynamic_find_value (dynamic, DT_RELAENT,   &rela_ent));
	LIB_ASSERT_OK(fail, dynamic_find_value (dynamic, DT_RELACOUNT, &rela_count));
  
	if(rela_ent != 0x18) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELOC_ENT;
	}
  
	if(rela_size != rela_count * rela_ent) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELOC_TABLE_SIZE;
	}
  
	Elf64_Rela *rela_base = (Elf64_Rela*) (module_base + rela_offset);
	for(uint64_t i = 0; i < rela_count; i++) {
		Elf64_Rela rela = rela_base[i];
    
		switch(rela.r_reloc_type) {
		case 0x403: // R_AARCH64_RELATIVE
			if(rela.r_symbol != 0) {
				return LIBTRANSISTOR_ERR_TRNLD_RELA_SYMBOL_UNSUPPORTED;
			}
			*(void**)(module_base + rela.r_offset) = module_base + rela.r_addend;
			break;
		default:
			return LIBTRANSISTOR_ERR_TRNLD_UNRECOGNIZED_RELOC_TYPE;
		}
	}
	
	return RESULT_OK;
fail:
	return r;
}

result_t ld_add_module(module_input_t input, module_t **out) {
	dbg_printf("queue %s", input.name);
	module_t *mod = malloc(sizeof(*mod));
	if(mod == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	memset(mod, 0, sizeof(*mod));
	mod->refcount = 1;
	mod->input = input;
	
	module_list_node_t *node = malloc(sizeof(*node));
	if(node == NULL) {
		free(mod);
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	node->module = mod;
	
	mod->state = MODULE_STATE_QUEUED;
	trn_list_add_tail(&module_list_head, &node->list);
	
	*out = mod;
	return RESULT_OK;
}

result_t ld_discover_module(const char *name_src, module_t **out) {
	dbg_printf("discovering %s", name_src);
	char name[0x301];
	strncpy(name, name_src, 0x300);
	name[0x300] = 0;

	int len = strlen(name);
	// strip .so suffix
	if(strcmp(name + len - 3, ".so") == 0) {
		len-= 3;
		name[len] = 0;
	}
	dbg_printf("transformed to %s", name);

	char path[0x301];
	for(uint64_t i = 0; i < ARRAY_LENGTH(ld_search_path); i++) {
		strncpy(path, ld_search_path[i], 0x300);
		path[0x300] = 0;
		int len = strlen(path);
		strncpy(path + len, name, 0x300-len);
		path[0x300] = 0;
		
		dbg_printf("try %s", path);
		FILE *f = fopen(path, "rb");
		if(f == NULL) {
			continue;
		}
		dbg_printf("got %s", path);
		if(fseek(f, 0, SEEK_END) != 0) {
			dbg_printf("fseek failure");
			fclose(f);
			continue;
		}
		ssize_t nro_size = ftell(f);
		if(nro_size == -1) {
			dbg_printf("ftell failure");
			fclose(f);
			continue;
		}
		if(fseek(f, 0, SEEK_SET) != 0) {
			dbg_printf("fseek failure");
			fclose(f);
			continue;
		}
		
		void *nro_buffer = alloc_pages(nro_size, nro_size, NULL);
		if(nro_buffer == NULL) {
			dbg_printf("failed to allocate space for nro");
			fclose(f);
			return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		}
		ssize_t total_read = 0;
		while(total_read < nro_size) {
			size_t r = fread(nro_buffer + total_read, 1, nro_size - total_read, f);
			if(r == 0) {
				dbg_printf("failed to read nro (read 0x%x/0x%x bytes): %d", total_read, nro_size, errno);
				free_pages(nro_buffer);
				fclose(f);
				return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
			}
			total_read+= r;
		}

		fclose(f);

		uint32_t nro_bss_size = *(uint32_t*)(nro_buffer + 0x38);
		void *nro_bss = alloc_pages(nro_bss_size, nro_bss_size, NULL);
		if(nro_bss == NULL) {
			dbg_printf("failed to allocate bss");
			free_pages(nro_buffer);
			return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		}
		
		result_t r;
		if((r = ro_init()) != RESULT_OK) {
			dbg_printf("failed to init ro");
			free_pages(nro_bss);
			free_pages(nro_buffer);
			return r;
		}

		// TODO: load NRR, modular loaders
		
		void *nro_base;
		if((r = ro_load_nro(&nro_base, nro_buffer, nro_size, nro_bss, nro_bss_size)) != RESULT_OK) {
			free_pages(nro_bss);
			free_pages(nro_buffer);
			return r;
		}

		dbg_printf("loaded NRO @ %p", nro_base);
		
		module_input_t input;
		input.name = name_src;
		input.base = nro_base;
		input.type = MODULE_TYPE_NRO_VIA_LDR_RO;
		input.nro_via_ldr_ro.nro_image = nro_buffer;
		input.nro_via_ldr_ro.bss = nro_bss;
		return ld_add_module(input, out);
	}
	return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_FIND_MODULE;
}

result_t ld_decref_module(module_t *mod) {
	dbg_printf("decref '%s'", mod->input.name);
	if(--(mod->refcount) == 0) {
		return ld_finalize_module(mod);
	}
	return RESULT_OK;
}

result_t ld_scan_module(module_t *mod) {
	result_t r;
	uint8_t *module_base = mod->input.base;
	module_header_t *mod_header = (module_header_t *)&module_base[*(uint32_t*) &module_base[4]];
	Elf64_Dyn *dynamic = (Elf64_Dyn*) (((uint8_t*) mod_header) + mod_header->dynamic_off);
	mod->dynamic = dynamic;
	
	const char mod_magic[] = "MOD0";
	if(mod_header->magic != *((uint32_t*) mod_magic)) {
		r = LIBTRANSISTOR_ERR_TRNLD_INVALID_MODULE_HEADER;
		goto fail_mod;
	}

	r = dynamic_find_offset(dynamic, DT_HASH, (void**) &mod->hash, module_base);
	if(r == RESULT_OK) {
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		goto fail_mod;
	}

	r = dynamic_find_offset(dynamic, DT_STRTAB, (void**) &mod->strtab, module_base);
	if(r == RESULT_OK) {
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		goto fail_mod;
	}

	r = dynamic_find_offset(mod->dynamic, DT_SYMTAB, (void**) &mod->symtab, mod->input.base);
	if(r == RESULT_OK) {
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		return r;
	}

	uint64_t syment;
	r = dynamic_find_value(mod->dynamic, DT_SYMENT, &syment);
	if(r == RESULT_OK) {
		if(syment != sizeof(Elf64_Sym)) {
			return LIBTRANSISTOR_ERR_TRNLD_INVALID_SYM_ENT;
		}
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		return r;
	}

	for(Elf64_Dyn *walker = dynamic; walker->d_tag != DT_NULL; walker++) {
		if(walker->d_tag == DT_NEEDED) {
			dbg_printf("needs %s", mod->strtab + walker->d_val);
			module_t *dep;
			LIB_ASSERT_OK(fail_mod, ld_discover_module(mod->strtab + walker->d_val, &dep));
			module_list_node_t *node = malloc(sizeof(*node));
			if(node == NULL) {
				ld_decref_module(dep);
				r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
				goto fail_mod;
			}
			node->module = dep;
			trn_list_add_tail(&mod->dependencies, &node->list);
		}
	}

	mod->state = MODULE_STATE_SCANNED;
	
	return RESULT_OK;

fail_mod:
	ld_finalize_module(mod);
	return r;
}

static uint64_t elf_hash(const uint8_t *name) {
	uint64_t h = 0;
	uint64_t g;
	while(*name) {
		h = (h << 4) + *name++;
		if((g = (h & 0xf0000000)) != 0) {
			h ^= g >> 24;
		}
		h&= ~g;
	}
	return h;
}

result_t ld_find_definition(Elf64_Sym *find, module_t *find_module, Elf64_Sym **def, module_t **defining_module) {
	if(find_module->strtab == NULL) { return LIBTRANSISTOR_ERR_TRNLD_NEEDS_STRTAB; }
	const char *find_name = find_module->strtab + find->st_name;
	uint64_t find_name_hash = elf_hash(find_name);
	trn_list_foreach(&module_list_head, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		module_t *try_mod = node->module;
		if(try_mod->symtab == NULL) { continue; }
		if(try_mod->strtab == NULL) { continue; }
		if(try_mod->hash != NULL) {
			uint32_t nbucket = try_mod->hash[0];
			uint32_t nchain = try_mod->hash[1];
			uint32_t index = try_mod->hash[2 + (find_name_hash % nbucket)];
			uint32_t *chains = try_mod->hash + 2 + nbucket;
			while(index != 0 && strcmp(find_name, try_mod->strtab + try_mod->symtab[index].st_name) != 0) {
				index = chains[index];
			}
			if(index == STN_UNDEF) {
				continue;
			}
			Elf64_Sym *sym = &try_mod->symtab[index];
			if(sym->st_shndx == SHN_UNDEF) {
				continue;
			}
			*def = sym;
			*defining_module = try_mod;
			dbg_printf("found %s in module'%s'@%p + 0x%lx", find_name, try_mod->input.name, try_mod->input.base, sym->st_value);
			return RESULT_OK;
		}
	}
	return LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL;
}

result_t ld_run_relocation_table(module_t *mod, uint32_t offset_tag, uint32_t size_tag) {
	void *raw_table;
	Elf64_Dyn *dynamic = mod->dynamic;
	result_t r = dynamic_find_offset(dynamic, offset_tag, &raw_table, mod->input.base);
	if(r == LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		return RESULT_OK;
	}
	if(r != RESULT_OK) {
		return r;
	}

	uint64_t table_size;
	LIB_ASSERT_OK(fail, dynamic_find_value(dynamic, size_tag, &table_size));

	uint64_t table_type = offset_tag;
	if(offset_tag == DT_JMPREL) {
		LIB_ASSERT_OK(fail, dynamic_find_value(dynamic, DT_PLTREL, &table_type));
		dbg_printf("jmprel table is type %d", table_type);
	}

	uint64_t ent_size;
	switch(table_type) {
	case DT_RELA:
		r = dynamic_find_value(dynamic, DT_RELAENT, &ent_size);
		if(r == LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
			ent_size = sizeof(Elf64_Rela);
		} else if(r == RESULT_OK && ent_size != sizeof(Elf64_Rela)) {
			return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELOC_ENT;
		} else if(r != RESULT_OK) {
			return r;
		}
		break;
	case DT_REL:
		r = dynamic_find_value(dynamic, DT_RELENT, &ent_size);
		if(r == LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
			ent_size = sizeof(Elf64_Rel);
		} else if(r == RESULT_OK && ent_size != sizeof(Elf64_Rel)) {
			return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELOC_ENT;
		} else if(r != RESULT_OK) {
			return r;
		}
		break;
	default:
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELOC_TABLE_TYPE;
	}

	if((table_size % ent_size) != 0) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELOC_TABLE_SIZE;
	}

	for(size_t offset = 0; offset < table_size; offset+= ent_size) {
		Elf64_Rela rela;
		switch(table_type) {
		case DT_RELA:
			rela = *(Elf64_Rela*) (raw_table + offset);
			break;
		case DT_REL: {
			Elf64_Rel rel = *(Elf64_Rel*) (raw_table + offset);
			rela.r_offset = rel.r_offset;
			rela.r_reloc_type = rel.r_reloc_type;
			rela.r_symbol = rel.r_symbol;
			break; }
		}

		void *symbol = NULL;
		module_t *defining_module = mod;
		if(rela.r_symbol != 0) {
			dbg_printf("need to resolve symbol %d", rela.r_symbol);
			if(mod->symtab == NULL) { return LIBTRANSISTOR_ERR_TRNLD_NEEDS_SYMTAB; }
			if(mod->strtab == NULL) { return LIBTRANSISTOR_ERR_TRNLD_NEEDS_STRTAB; }
			Elf64_Sym *sym = &mod->symtab[rela.r_symbol];
			dbg_printf("  -> %s", mod->strtab + sym->st_name);
			
			Elf64_Sym *def;
			if((r = ld_find_definition(sym, mod, &def, &defining_module)) != RESULT_OK) {
				dbg_printf("while resolving %s", mod->strtab + sym->st_name);
				return r;
			}
			symbol = defining_module->input.base + def->st_value;
		}
		void *delta_symbol = defining_module->input.base;
		
		switch(rela.r_reloc_type) {
		case 1026: { // R_AARCH64_JUMP_SLOT
			void **target = (void**)(mod->input.base + rela.r_offset);
			if(table_type == DT_REL) {
				dbg_printf("table is DT_REL");
				rela.r_addend = *target;
			}
			dbg_printf("relocating to %p", symbol + rela.r_addend);
			*target = symbol + rela.r_addend;
			break; }
		case 1027: { // R_AARCH64_RELATIVE
			void **target = (void**)(mod->input.base + rela.r_offset);
			if(table_type == DT_REL) { // TODO: be careful here if the module was already relocated
				rela.r_addend = *target;
			}
			*target = delta_symbol + rela.r_addend;
			break; }
		default:
			dbg_printf("unknown relocation: 0x%x", rela.r_reloc_type);
			break;
		}
	}
	
	return RESULT_OK;
fail:
	return r;
}

result_t ld_relocate_module(module_t *mod) {
	dbg_printf("relocating module %s", mod->input.name);
	result_t r;
	r = ld_run_relocation_table(mod, DT_RELA,   DT_RELASZ); dbg_printf("DT_RELA -> 0x%x", r);
	r = ld_run_relocation_table(mod, DT_REL,    DT_RELSZ); dbg_printf("DT_REL -> 0x%x", r);
	r = ld_run_relocation_table(mod, DT_JMPREL, DT_PLTRELSZ); dbg_printf("DT_JMPREL -> 0x%x", r);
	return RESULT_OK;
}

result_t ld_process_modules() {
	trn_list_foreach(&module_list_head, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		if(node->module->state == MODULE_STATE_QUEUED) {
			ld_scan_module(node->module); // TODO: how to handle error
		}
	}
	trn_list_foreach(&module_list_head, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		if(node->module->state == MODULE_STATE_SCANNED) {
			ld_relocate_module(node->module); // TODO: how to handle error
		}
	}
	return RESULT_OK;
}

result_t ld_finalize_module(module_t *mod) {
	result_t r;
	dbg_printf("finalize '%s'", mod->input.name);
	
	trn_list_foreach(&mod->dependencies, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		ld_decref_module(node->module); // TODO: errors?
		free(node);
	}
	
	switch(mod->input.type) {
	case MODULE_TYPE_MAIN:
		free(mod);
		return RESULT_OK;
	case MODULE_TYPE_NRO_VIA_LDR_RO:
		r = ro_unload_nro(mod->input.base, mod->input.nro_via_ldr_ro.nro_image);
		free_pages(mod->input.nro_via_ldr_ro.nro_image);
		free_pages(mod->input.nro_via_ldr_ro.bss);
		free(mod);
		return r;
	default:
		free(mod);
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_MODULE_TYPE;
	}
	// TODO
	free(mod);
}
