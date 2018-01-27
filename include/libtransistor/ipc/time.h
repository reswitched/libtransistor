/**
 * @file libtransistor/ipc/time.h
 * @brief Time Services
 */

#pragma once

#include<libtransistor/types.h>

ipc_object_t time_systemclock_user;
ipc_object_t time_systemclock_network;
ipc_object_t time_systemclock_local;

/**
* @brief Initialize Time service
*/
result_t time_init();

/**
* @brief Get the current system time from one of the systemclocks
*/
result_t time_systemclock_get_current_time(ipc_object_t systemclock, uint64_t *time);

/**
* @brief Set the current system time for one of the systemclocks
*/
result_t time_systemclock_set_current_time(ipc_object_t systemclock, uint64_t *time);

/**
* @brief Finalize Time service
*/
result_t time_finalize();
