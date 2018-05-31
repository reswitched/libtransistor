#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/tls.h>

#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>
#include<libtransistor/ld/module.h>
#include<libtransistor/ld/internal.h>

#include<stdint.h>
#include<stdlib.h>
#include<string.h>

const bool RELOCATION_DEBUG = false; // run under Mephisto with --relocate

result_t ld_relocate_module_basic(uint8_t *module_base) {
	module_header_t *mod_header = (module_header_t *)&module_base[*(uint32_t*) &module_base[4]];
	Elf64_Dyn *dynamic = (Elf64_Dyn*) (((uint8_t*) mod_header) + mod_header->dynamic_off);
	uint64_t rela_offset = 0;
	uint64_t rela_size = 0;
	uint64_t rela_ent = 0;
	uint64_t rela_count = 0;

	if(mod_header->magic != 0x30444f4d) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_MODULE_HEADER;
	}

	result_t r;
	LIB_ASSERT_OK(fail, elf_dynamic_find_value (dynamic, DT_RELA,      &rela_offset));
	LIB_ASSERT_OK(fail, elf_dynamic_find_value (dynamic, DT_RELASZ,    &rela_size));
	LIB_ASSERT_OK(fail, elf_dynamic_find_value (dynamic, DT_RELAENT,   &rela_ent));
	LIB_ASSERT_OK(fail, elf_dynamic_find_value (dynamic, DT_RELACOUNT, &rela_count));
  
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

static result_t ld_run_relocation_table(module_t *mod, uint32_t offset_tag, uint32_t size_tag) {
	void *raw_table;
	Elf64_Dyn *dynamic = mod->dynamic;
	result_t r = elf_dynamic_find_offset(dynamic, offset_tag, &raw_table, mod->input.base);
	if(r == LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		return RESULT_OK;
	}
	if(r != RESULT_OK) {
		return r;
	}

	uint64_t table_size;
	LIB_ASSERT_OK(fail, elf_dynamic_find_value(dynamic, size_tag, &table_size));

	uint64_t table_type = offset_tag;
	if(offset_tag == DT_JMPREL) {
		LIB_ASSERT_OK(fail, elf_dynamic_find_value(dynamic, DT_PLTREL, &table_type));
	}

	uint64_t ent_size;
	switch(table_type) {
	case DT_RELA:
		r = elf_dynamic_find_value(dynamic, DT_RELAENT, &ent_size);
		if(r == LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
			ent_size = sizeof(Elf64_Rela);
		} else if(r == RESULT_OK && ent_size != sizeof(Elf64_Rela)) {
			return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELOC_ENT;
		} else if(r != RESULT_OK) {
			return r;
		}
		break;
	case DT_REL:
		r = elf_dynamic_find_value(dynamic, DT_RELENT, &ent_size);
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
			if(mod->symtab == NULL) { return LIBTRANSISTOR_ERR_TRNLD_NEEDS_SYMTAB; }
			if(mod->strtab == NULL) { return LIBTRANSISTOR_ERR_TRNLD_NEEDS_STRTAB; }
			Elf64_Sym *sym = &mod->symtab[rela.r_symbol];
			
			Elf64_Sym *def;
			if((r = ld_resolve_load_symbol(mod, mod->strtab + sym->st_name, &def, &defining_module)) != RESULT_OK) {
				dbg_printf("while resolving %s: 0x%x", mod->strtab + sym->st_name, r);
				return r;
			}
			symbol = defining_module->input.base + def->st_value;
		}
		void *delta_symbol = defining_module->input.base;
		
		switch(rela.r_reloc_type) {
		case 257: // R_AARCH64_ABS64
			// fall-through
		case 1025: // R_AARCH64_GLOB_DAT
			// fall-through
		case 1026: { // R_AARCH64_JUMP_SLOT
			void **target = (void**)(mod->input.base + rela.r_offset);
			if(table_type == DT_REL) {
				rela.r_addend = *target;
			}
			*target = symbol + rela.r_addend;
			break; }
		case 1027: { // R_AARCH64_RELATIVE
			if(!mod->input.has_run_basic_relocations) {
				void **target = (void**)(mod->input.base + rela.r_offset);
				if(table_type == DT_REL) { // TODO: be careful here if the module was already relocated
					rela.r_addend = *target;
				}
				*target = delta_symbol + rela.r_addend;
			}
			break; }
		default:
			dbg_printf("unknown relocation: 0x%x", rela.r_reloc_type);
			return LIBTRANSISTOR_ERR_TRNLD_UNRECOGNIZED_RELOC_TYPE;
		}
	}
	
	return RESULT_OK;
fail:
	return r;
}

result_t ld_relocate_module(module_t *mod) {
	result_t r;
	LIB_ASSERT_OK(fail, ld_run_relocation_table(mod, DT_RELA,   DT_RELASZ));
	LIB_ASSERT_OK(fail, ld_run_relocation_table(mod, DT_REL,    DT_RELSZ));
	LIB_ASSERT_OK(fail, ld_run_relocation_table(mod, DT_JMPREL, DT_PLTRELSZ));
	mod->state = MODULE_STATE_RELOCATED;
fail:
	return r;
}
