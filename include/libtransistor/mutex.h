/**
 * @file libtransistor/mutex.h
 * @brief Mutex functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<stdatomic.h>

typedef struct {
	volatile atomic_uint_fast64_t lock;
} trn_mutex_t;

typedef struct {
	trn_mutex_t mutex;
	thread_h owner;
	int count;
} trn_recursive_mutex_t;

void trn_mutex_create(trn_mutex_t *mutex);
void trn_mutex_lock(trn_mutex_t *mutex);
bool trn_mutex_try_lock(trn_mutex_t *mutex); // true on success
void trn_mutex_unlock(trn_mutex_t *mutex);
void trn_recursive_mutex_create(trn_recursive_mutex_t *recursive);
void trn_recursive_mutex_lock(trn_recursive_mutex_t *recursive);
bool trn_recursive_mutex_try_lock(trn_recursive_mutex_t *recursive); // true on success
void trn_recursive_mutex_unlock(trn_recursive_mutex_t *recursive);

#ifdef __cplusplus
}
#endif
