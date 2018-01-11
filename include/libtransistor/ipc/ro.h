/**
 * @file libtransistor/ipc/ro.h
 * @brief Loader Services
 */

#pragma once

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
* @param nro_base Description here...
* @param nro_heap Description here...
* @param nro_size Description here...
* @param nro_bss Description here...
* @param bss_size Description here...
*/
result_t ro_load_nro(void **nro_base, void *nro_heap, uint64_t nro_size, void *nro_bss, uint64_t bss_size);

/**
* @brief Description here...
*
* @param nro_base Description here...
* @param nro_heap Description here...
*/
result_t ro_unload_nro(void *nro_base, void *nro_heap);

/**
* @brief Description here...
*
* @param nrr_heap Description here...
* @param nrr_size Description here...
*/
result_t ro_load_nrr(void *nrr_heap, uint64_t nrr_size);

/**
* @brief Description here...
*
* @param nrr_heap Description here...
*/
result_t ro_unload_nrr(void *nrr_heap);
