/**
 * @file libtransistor/ld/loader/loaders.h
 * @brief List of loaders for dynamic linker
 */

#pragma once

#include<libtransistor/ld/ld.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ld_loader_t {
	result_t (*can_load)(void *file, size_t file_size);
	// takes ownership of file upon success, which is assumed to be a buffer freeable via \ref alloc_pages
	result_t (*load)(module_input_t *spec_out, void *file, size_t file_size);
	result_t (*unload)(module_input_t *spec);
} ld_loader_t;

extern ld_loader_t ld_loader_nro_via_svc;
extern ld_loader_t ld_loader_nro_via_ldr_ro;

#ifdef __cplusplus
}
#endif
