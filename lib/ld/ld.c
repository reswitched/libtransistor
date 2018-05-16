#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/ipc/ro.h>

#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>
#include<libtransistor/ld/module.h>
#include<libtransistor/ld/internal.h>
#include<libtransistor/ld/loaders.h>

#include<stdint.h>
#include<stdlib.h>
#include<string.h>

trn_list_head_t ld_module_list_head = TRN_LIST_HEAD_INITIALIZER;

	module_t *mod = malloc(sizeof(*mod));
result_t ld_add_module(module_input_t input, module_t **out) {
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
	trn_list_add_tail(&ld_module_list_head, &node->list);
	
	*out = mod;
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
		goto fail;
	}

	r = elf_dynamic_find_offset(dynamic, DT_HASH, (void**) &mod->hash, module_base);
	if(r == RESULT_OK) {
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		goto fail;
	}

	r = elf_dynamic_find_offset(dynamic, DT_STRTAB, (void**) &mod->strtab, module_base);
	if(r == RESULT_OK) {
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		goto fail;
	}

	r = elf_dynamic_find_offset(mod->dynamic, DT_SYMTAB, (void**) &mod->symtab, mod->input.base);
	if(r == RESULT_OK) {
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		return r;
	}

	uint64_t syment;
	r = elf_dynamic_find_value(mod->dynamic, DT_SYMENT, &syment);
	if(r == RESULT_OK) {
		if(syment != sizeof(Elf64_Sym)) {
			return LIBTRANSISTOR_ERR_TRNLD_INVALID_SYM_ENT;
		}
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		return r;
	}

	for(Elf64_Dyn *walker = dynamic; walker->d_tag != DT_NULL; walker++) {
		if(walker->d_tag == DT_NEEDED) {
			module_t *dep;
			LIB_ASSERT_OK(fail, ld_discover_module(mod->strtab + walker->d_val, &dep, mod->input.is_global));
			module_list_node_t *node = malloc(sizeof(*node));
			if(node == NULL) {
				ld_decref_module(dep);
				r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
				goto fail;
			}
			node->module = dep;
			trn_list_add_tail(&mod->dependencies, &node->list);
		}
	}

	mod->state = MODULE_STATE_SCANNED;
	
	return RESULT_OK;

fail:
	return r;
}

result_t ld_initialize_module(module_t *mod) {
	if(mod->state != MODULE_STATE_RELOCATED) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_MODULE_STATE;
	}
	
	void (**init_array)(void);
	ssize_t init_array_size;

	result_t r;
	r = elf_dynamic_find_offset(mod->dynamic, DT_INIT_ARRAY, (void**) &init_array, mod->input.base);
	if(r == RESULT_OK) {
		LIB_ASSERT_OK(fail, elf_dynamic_find_value(mod->dynamic, DT_INIT_ARRAYSZ, &init_array_size));
		// run all of the initializers
		for(size_t i = 0; i < init_array_size/sizeof(init_array[0]); i++) {
			init_array[i]();
		}
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		goto fail;
	}

	mod->state = MODULE_STATE_INITIALIZED;
	return RESULT_OK;
fail:
	return r;
}

result_t ld_finalize_module(module_t *mod) {
	if(mod->state != MODULE_STATE_INITIALIZED) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_MODULE_STATE;
	}
	
	void (**fini_array)(void);
	ssize_t fini_array_size;

	result_t r;
	r = elf_dynamic_find_offset(mod->dynamic, DT_FINI_ARRAY, (void**) &fini_array, mod->input.base);
	if(r == RESULT_OK) {
		LIB_ASSERT_OK(fail, elf_dynamic_find_value(mod->dynamic, DT_FINI_ARRAYSZ, &fini_array_size));
		// run all of the finalizers
		for(size_t i = 0; i < fini_array_size/sizeof(fini_array[0]); i++) {
			fini_array[i]();
		}
	} else if(r != LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY) {
		goto fail;
	}

	mod->state = MODULE_STATE_FINALIZED;
	return RESULT_OK;
fail:
	return r;
}

result_t ld_process_modules() {
	result_t r;
	trn_list_foreach(&ld_module_list_head, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		if(node->module->state == MODULE_STATE_QUEUED) {
			LIB_ASSERT_OK(fail, ld_scan_module(node->module));
		}
	}
	trn_list_foreach(&ld_module_list_head, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		if(node->module->state == MODULE_STATE_SCANNED) {
			LIB_ASSERT_OK(fail, ld_relocate_module(node->module));
		}
	}
	trn_list_foreach(&ld_module_list_head, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		if(node->module->state == MODULE_STATE_RELOCATED) {
			LIB_ASSERT_OK(fail, ld_initialize_module(node->module));
		}
	}
fail:
	return r;
}

result_t ld_decref_module(module_t *mod) {
	if(--(mod->refcount) == 0) {
		return ld_destroy_module(mod);
	}
	return RESULT_OK;
}

result_t ld_destroy_module(module_t *mod) {
	result_t r = RESULT_OK;
	if(mod->state == MODULE_STATE_INITIALIZED) {
		ld_finalize_module(mod);
	}
	
	trn_list_foreach(&mod->dependencies, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		ld_decref_module(node->module);
		free(node);
	}

	if(mod->input.loader) {
		mod->input.loader->unload(&mod->input);
	}

	trn_list_foreach(&ld_module_list_head, i) {
		module_list_node_t *node = trn_list_entry(module_list_node_t, list, i);
		if(node->module == mod) {
			trn_list_delink(i);
			i = i->prev;
			free(node);
		}
	}
	
	free(mod);
	return r;
}
