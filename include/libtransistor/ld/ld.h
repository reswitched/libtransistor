/**
 * @file libtransistor/ld/ld.h
 * @brief Dynamic linking functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct module_t module_t;

/**
 * @brief Perform basic relocations on a module.
 * Does not require \ref ld_init
 */
result_t ld_basic_relocate_module(uint8_t *module_base);

/**
 * @brief Initialize dynamic linker
 */
result_t ld_init();

/**
 * @brief Queues a module to processes full relocations, dynamic library dependencies, and initializers
 */
result_t ld_queue_module(const char *name, uint8_t *base, bool owned_by_loader, module_t **out);

/**
 * @brief Discovers a module in the filesystem and queues it
 */
result_t ld_discover_module(const char *name, module_t **out);

/**
 * @brief Processes all modules
 */
result_t ld_process_modules();

/**
 * @brief Unloads a module and its dependencies
 */
result_t ld_finalize_module(module_t *module);

void ld_finalize();

#ifdef __cplusplus
}
#endif
