#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>

#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>
#include<libtransistor/ld/module.h>
#include<libtransistor/ld/internal.h>

#include<stdint.h>
#include<stdlib.h>
#include<string.h>

static result_t ld_try_resolve_symbol(module_t *try_mod, const char *find_name, uint64_t find_name_hash, Elf64_Sym **def, module_t **defining_module, bool require_global) {
	if(require_global && !try_mod->input.is_global) { return LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL; }
	if(try_mod->symtab == NULL) { return LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL; }
	if(try_mod->strtab == NULL) { return LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL; }
	if(try_mod->hash != NULL) {
		uint32_t nbucket = try_mod->hash[0];
		uint32_t nchain = try_mod->hash[1]; (void) nchain;
		uint32_t index = try_mod->hash[2 + (find_name_hash % nbucket)];
		uint32_t *chains = try_mod->hash + 2 + nbucket;
		while(index != 0 && strcmp(find_name, try_mod->strtab + try_mod->symtab[index].st_name) != 0) {
			index = chains[index];
		}
		if(index == STN_UNDEF) {
			return LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL;
		}
		Elf64_Sym *sym = &try_mod->symtab[index];
		if(sym->st_shndx == SHN_UNDEF) {
			return LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL;
		}
		*def = sym;
		*defining_module = try_mod;
		return RESULT_OK;
	}
	return LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL;
}

result_t ld_resolve_load_symbol(module_t *find_mod, const char *find_name, Elf64_Sym **def, module_t **defining_module) {
	uint64_t find_name_hash = elf_hash_string(find_name);
	trn_list_foreach(&ld_module_list_head, i) {
		result_t r = ld_try_resolve_symbol(trn_list_entry(module_list_node_t, list, i)->module, find_name, find_name_hash, def, defining_module, true);
		if(r == LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL) {
			continue;
		} else { // this includes RESULT_OK
			return r;
		}
	}

	// use last-resort module
	if(find_mod != NULL) {
		return ld_try_resolve_symbol(find_mod, find_name, find_name_hash, def, defining_module, false);
	}
	
	return LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL;
}

result_t ld_resolve_dependency_symbol(module_t *find_mod, const char *find_name, Elf64_Sym **def, module_t **defining_module) {
	uint64_t find_name_hash = elf_hash_string(find_name);
	result_t r;
	r = ld_try_resolve_symbol(find_mod, find_name, find_name_hash, def, defining_module, false);
	if(r != LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL) { // this includes RESULT_OK
		return r;
	}
	trn_list_foreach(&find_mod->dependencies, i) {
		r = ld_try_resolve_symbol(trn_list_entry(module_list_node_t, list, i)->module, find_name, find_name_hash, def, defining_module, false);
		if(r == LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL) {
			continue;
		} else { // this includes RESULT_OK
			return r;
		}
	}
	trn_list_foreach(&find_mod->dependencies, i) {
		r = ld_resolve_dependency_symbol(trn_list_entry(module_list_node_t, list, i)->module, find_name, def, defining_module);
		if(r == LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL) {
			continue;
		} else { // this includes RESULT_OK
			return r;
		}
	}
	return LIBTRANSISTOR_ERR_TRNLD_COULD_NOT_RESOLVE_SYMBOL;
}
