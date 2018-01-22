/**
 * @file libtransistor/ipc/bpc.h
 * @brief Board Power Control
 */

#pragma once

#include<libtransistor/types.h>

/**
* @brief Initialize BPC
*/
result_t bpc_init();

/**
* @brief Shutdown the system - should never return RESULT_OK
*/
result_t bpc_shutdown_system();

/**
* @brief Reboot the system - should never return RESULT_OK
*/
result_t bpc_reboot_system();

/**
* @brief Finalize BPC
*/
void bpc_finalize();
