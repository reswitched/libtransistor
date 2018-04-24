/**
 * @file libtransistor/ipc/fatal.h
 * @brief Fatal error services
 */

#pragma once

#include<libtransistor/types.h>

/**
 * @brief Initialize fatal error service
 */
result_t fatal_init();

/**
 * @brief Transition to a fatal error state
 */
result_t fatal_transition_to_fatal_error(result_t code, uint64_t unknown);

/**
 * @brief Finalize fatal error service
 */
void fatal_finalize();
