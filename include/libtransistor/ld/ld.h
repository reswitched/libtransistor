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

typedef enum {
	MODULE_TYPE_INVALID = 0,
	MODULE_TYPE_MAIN, // loaded by an external loader
	MODULE_TYPE_NRO_VIA_LDR_RO, // loaded NRO by ldr:ro
} module_type_t;

typedef struct {
	const char *name;
	void *base;
	module_type_t type;
	union {
		struct {
			void *nro_image;
			void *bss;
		} nro_via_ldr_ro;
	};
} module_input_t;

/**
 * @brief Adds a loaded module to the end of the processing queue.
 */
result_t ld_add_module(module_input_t input, module_t **out);

/**
 * @brief Discovers a module in the filesystem, loads it, and adds it to the processing queue
 */
result_t ld_discover_module(const char *name, module_t **out);

/**
 * @brief Processes all modules in the queue
 */
result_t ld_process_modules();

/**
 * @brief Decrements the module's reference count and unloads it if it has reached zero
 */
result_t ld_decref_module(module_t *module);

void ld_finalize();

#ifdef __cplusplus
}
#endif
