/**
 * @file libtransistor/ipc/time.h
 * @brief Time Services
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

typedef struct system_clock_t system_clock_t;

extern system_clock_t *time_system_clock_user;
extern system_clock_t *time_system_clock_network;
extern system_clock_t *time_system_clock_local;

/**
* @brief Initialize Time service
*/
result_t time_init();

/**
* @brief Get the current system time from one of the system clocks
*/
result_t time_system_clock_get_current_time(system_clock_t *system_clock, uint64_t *time);

/**
* @brief Set the current system time for one of the system clocks
*/
result_t time_system_clock_set_current_time(system_clock_t *system_clock, uint64_t time);

/**
* @brief Finalize Time service
*/
void time_finalize();

#ifdef __cplusplus
}
#endif
