/**
 * @file libtransistor/ld/module.h
 * @brief Module structure and operations for internal use in the dynamic linker
 */

#pragma once

#include<libtransistor/collections/list.h>
#include<libtransistor/ld/elf.h>

#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	MODULE_STATE_INVALID = 0,
	MODULE_STATE_QUEUED = 1,
	MODULE_STATE_SCANNED = 2,
	MODULE_STATE_RELOCATED = 3,
	MODULE_STATE_INITIALIZED = 4,
	MODULE_STATE_FINALIZED = 5,
	MODULE_STATE_UNLOADED = 6,
} module_state_t;

typedef struct {
	module_t *module;
	trn_list_head_t list;
} module_list_node_t;

struct module_t {
	module_state_t state;
	int refcount;
	
	// needed for MODULE_STATE_QUEUED
	module_input_t input;

	trn_list_head_t dependencies;
	
	Elf64_Dyn *dynamic;
	Elf64_Sym *symtab;
	const char *strtab;
	uint32_t *hash;

	bool is_global;
};

// module operations
result_t ld_scan_module(module_t *mod);
result_t ld_relocate_module(module_t *mod);
result_t ld_initialize_module(module_t *mod);
result_t ld_finalize_module(module_t *mod);
result_t ld_destroy_module(module_t *mod);
// \ref ld_decref_module is a public API and goes in ld.h

#ifdef __cplusplus
}
#endif
