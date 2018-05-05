/**
 * @file libtransistor/ld/ld.h
 * @brief Dynamic linking functions
 */

#pragma once

#include<libtransistor/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct module_t module_t;
typedef struct ld_loader_t ld_loader_t;

/**
 * @brief Perform basic relocations on a module.
 */
result_t ld_relocate_module_basic(uint8_t *module_base);

typedef struct {
	const char *name;
	void *base;
	ld_loader_t *loader;
	void *loader_data;
} module_input_t;

/**
 * @brief Adds a loaded module to the end of the processing queue.
 * @param is_global Whether or not to also add it to the load-order for symbol resolution
 *                  in relocation processing.
 */
result_t ld_add_module(module_input_t input, module_t **out, bool is_global);

/**
 * @brief Discovers a module in the filesystem, loads it, and adds it to the processing queue
 * @param is_global Whether or not this module and its dependencies will provide symbols
 *                  usable for relocation processing.
 */
result_t ld_discover_module(const char *name, module_t **out, bool is_global);

/**
 * @brief Decrements the module's reference count and finalizes, unloads, and destroys it if it has reached zero
 */
result_t ld_decref_module(module_t *module);

/**
 * @brief Processes all modules in the queue
 */
result_t ld_process_modules();

void ld_finalize();

#ifdef __cplusplus
}
#endif
