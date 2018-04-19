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

result_t ld_resolve_symbol(Elf64_Sym *find, module_t *find_module, Elf64_Sym **def, module_t **defining_module) {
	if(find_module->strtab == NULL) { return LIBTRANSISTOR_ERR_TRNLD_NEEDS_STRTAB; }
	const char *find_name = find_module->strtab + find->st_name;
	uint64_t find_name_hash = elf_hash_string(find_name);
	trn_list_foreach(&ld_module_list_head, i) {
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
