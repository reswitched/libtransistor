/**
 * @file libtransistor/ld/module.h
 * @brief Module structure
 */

#pragma once

#include<libtransistor/collections/list.h>

#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	MODULE_STATE_INVALID = 0,
	MODULE_STATE_QUEUED = 1,
	MODULE_STATE_PROCESSED = 2,
	MODULE_STATE_UNLOADED = 3,
} module_state_t;

typedef struct {
	module_t *module;
	trn_list_head_t list;
} module_list_node_t;

struct module_t {
	module_state_t state;
	int refcount;
	
	// needed for MODULE_STATE_QUEUED
	const char *name;
	void *base;

	trn_list_head_t dependencies;
	
	bool has_rela;
	uint64_t rela_offset;
	uint64_t rela_size;
	uint64_t rela_ent;
	uint64_t rela_count;
	const char *strtab;
};

#ifdef __cplusplus
}
#endif
