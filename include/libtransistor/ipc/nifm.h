/**
 * @file libtransistor/ipc/nifm.h
 * @brief Network Interface Manager
 */

#pragma once

#include<libtransistor/types.h>

/**
* @brief Initialize Network Interface Manager
*/
result_t nifm_init();

/**
* @brief Get the system's ip address
*/
result_t nifm_get_ip_address(uint32_t *ip);

/**
* @brief Finalize Network Interface Manager
*/
void nifm_finalize();
