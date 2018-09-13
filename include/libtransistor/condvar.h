/**
 * @file libtransistor/condvar.h
 * @brief Condition variables
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/mutex.h>

typedef struct {
	uint32_t key;
} trn_condvar_t;

#define TRN_CONDVAR_STATIC_INITIALIZER {.key = 0}

/**
 * @brief Creates a condition variable
 *
 * Alternatively, a statically allocated condition variable
 * may be initialized with /ref TRN_CONDVAR_STATIC_INITIALIZER
 */
void trn_condvar_create(trn_condvar_t *condvar);

/**
 * @brief Signals n threads waiting on the condition variable, or -1 for all of them
 */
result_t trn_condvar_signal(trn_condvar_t *condvar, int n);

/**
 * @brief Waits for the condition variable to be signalled
 * 
 * @param timeout How long (in nanoseconds) to wait, or -1 for no timeout
 */
result_t trn_condvar_wait(trn_condvar_t *condvar, trn_mutex_t *mutex, uint64_t timeout) REQUIRES(mutex);

/**
 * @brief Destroys a condition variable
 */
void trn_condvar_destroy(trn_condvar_t *condvar);

#ifdef __cplusplus
}
#endif
