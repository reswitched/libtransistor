/**
 * @file libtransistor/ld/loder/nro_via_ldr_ro.h
 * @brief Loader for NRO files using svcMapProcessCodeMemory
 */

#pragma once

#include<libtransistor/ld/ld.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Loads an NRO
 * Takes ownership of nro_image on success, which is assumed to be a buffer freeable via \ref free_pages.
 */
result_t ld_nro_via_svc_load(module_input_t *spec_out, void *nro_image, size_t nro_image_size);

/**
 * @brief Unloads an NRO
 */
result_t ld_nro_via_svc_unload(module_input_t *spec);

#ifdef __cplusplus
}
#endif
