/**
 * @file libtransistor/ipc/time.h
 * @brief Time Services
 */

#pragma once

#include<libtransistor/types.h>

/**
* @brief Initialize Time service
*/
result_t time_init();

/**
* @brief Get the current system time
*/
result_t time_get_current_time(uint64_t *time);

/**
* @brief Finalize Time service
*/
result_t time_finalize();
