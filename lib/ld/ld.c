#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>

#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>
#include<libtransistor/ld/module.h>

#include<stdint.h>
#include<stdlib.h>
#include<string.h>

const bool RELOCATION_DEBUG = false; // run under Mephisto with --relocate

static trn_list_head_t module_list_head = TRN_LIST_HEAD_INITIALIZER;

typedef struct {
	uint32_t magic, dynamic_off, bss_start_off, bss_end_off;
	uint32_t unwind_start_off, unwind_end_off, module_object_off;
} module_header_t;

static result_t dynamic_find_value(Elf64_Dyn *dynamic, int64_t tag, uint64_t *value) {
	uint64_t *found = NULL;
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
	bool found_rela = false;

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
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELA_ENT;
	}
  
	if(rela_size != rela_count * rela_ent) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELA_SIZE;
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

result_t ld_queue_module(const char *name, uint8_t *base, module_t **out) {
	dbg_printf("queue %s", name);
	module_t *mod = malloc(sizeof(*mod));
	if(mod == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	memset(mod, 0, sizeof(*mod));
	mod->refcount = 1;
	mod->name = name;
	mod->base = base;
	
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

result_t ld_discover_module(const char *name, module_t **out) {
	dbg_printf("discovering %s", name);
	return ld_queue_module(name, NULL, out);
}

result_t ld_decref_module(module_t *mod) {
	if(--(mod->refcount) == 0) {
		return ld_finalize_module(mod);
	}
	return RESULT_OK;
}

result_t ld_process_module(module_t *mod) {
	dbg_printf("processing module %s", mod->name);
	result_t r;
	uint8_t *module_base = mod->base;
	module_header_t *mod_header = (module_header_t *)&module_base[*(uint32_t*) &module_base[4]];
	Elf64_Dyn *dynamic = (Elf64_Dyn*) (((uint8_t*) mod_header) + mod_header->dynamic_off);

	const char mod_magic[] = "MOD0";
	if(mod_header->magic != *((uint32_t*) mod_magic)) {
		r = LIBTRANSISTOR_ERR_TRNLD_INVALID_MODULE_HEADER;
		goto fail_mod;
	}

	LIB_ASSERT_OK(fail_mod, dynamic_find_value (dynamic, DT_RELA,      &mod->rela_offset));
	LIB_ASSERT_OK(fail_mod, dynamic_find_value (dynamic, DT_RELASZ,    &mod->rela_size));
	LIB_ASSERT_OK(fail_mod, dynamic_find_value (dynamic, DT_RELAENT,   &mod->rela_ent));
	LIB_ASSERT_OK(fail_mod, dynamic_find_value (dynamic, DT_RELACOUNT, &mod->rela_count));
	LIB_ASSERT_OK(fail_mod, dynamic_find_offset(dynamic, DT_STRTAB,    &mod->strtab, module_base));
	
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
			node->module = mod;
			trn_list_add_tail(&mod->dependencies, &node->list);
		}
	}
	
	if(mod->rela_ent != 0x18) {
		r = LIBTRANSISTOR_ERR_TRNLD_INVALID_RELA_ENT;
		goto fail_mod;
	}
  
	if(mod->rela_size != mod->rela_count * mod->rela_ent) {
		r = LIBTRANSISTOR_ERR_TRNLD_INVALID_RELA_SIZE;
		goto fail_mod;
	}
	
	return RESULT_OK;
fail_mod:
	trn_list_foreach(&mod->dependencies, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		ld_decref_module(node->module);
		free(node);
	}
	
	free(mod);
	return r;
}

result_t ld_process_modules() {
	dbg_printf("processing modules");
	trn_list_foreach(&module_list_head, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		if(node->module->state == MODULE_STATE_QUEUED) {
			ld_process_module(node->module); // TODO: how to handle error
		}
	}
}

result_t ld_finalize_module(module_t *mod) {
	// TODO
	free(mod);
}
