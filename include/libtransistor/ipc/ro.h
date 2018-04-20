/**
 * @file libtransistor/ipc/ro.h
 * @brief Loader Services
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <libtransistor/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/**
* @brief Initialize Loader Services
*/
result_t ro_init();

/**
* @brief Finalize Loader Services
*/
void ro_finalize();


/**
* @brief Description here...
*
* @param nro_base Pointer to newly-loaded NRO base
* @param nro_heap Pointer to NRO image
* @param nro_size Size of NRO image
* @param nro_bss Pointer to backing memory for bss
* @param bss_size Size of backing memory for bss
*/
result_t ro_load_nro(void **nro_base, void *nro_heap, uint64_t nro_size, void *nro_bss, uint64_t bss_size);

/**
* @brief Description here...
*
* @param nro_base Pointer to loaded NRO
* @param nro_heap Pointer to original NRO image
*/
result_t ro_unload_nro(void *nro_base, void *nro_heap);

/**
* @brief Description here...
*
* @param nrr_heap Pointer to NRR
* @param nrr_size Size of NRR
*/
result_t ro_load_nrr(void *nrr_heap, uint64_t nrr_size);

/**
* @brief Description here...
*
* @param nrr_heap Pointer to NRR
*/
result_t ro_unload_nrr(void *nrr_heap);

session_h ro_get_service_handle();

#ifdef __cplusplus
}
#endif
