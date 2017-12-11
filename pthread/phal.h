#pragma once

#include <stdint.h>
#include <phal_types.h>

int phal_thread_create(phal_tid *tid, void (*start_routine)(void*), void *arg);
void phal_thread_exit(phal_tid *tid);

// Called after the thread exited, to free up any potential resources
int phal_thread_destroy(phal_tid *tid);
void **phal_get_tls();

int phal_semaphore_create(phal_semaphore *sem);
int phal_semaphore_destroy(phal_semaphore *sem);
int phal_semaphore_signal(phal_semaphore *sem);
int phal_semaphore_wait(phal_semaphore *sem, phal_mutex *mutex, uint64_t timeout);

int phal_mutex_create(phal_mutex *mutex);
int phal_mutex_destroy(phal_mutex *mutex);
int phal_mutex_lock(phal_mutex *mutex);
int phal_mutex_unlock(phal_mutex *mutex);

// TODO: pass timespec instead
int phal_thread_sleep(uint64_t msec);
