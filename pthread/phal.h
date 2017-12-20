#pragma once

#include <stdint.h>
#include <time.h>
#include <phal_types.h>

int phal_thread_create(phal_tid *tid, void (*start_routine)(void*), void *arg);
void phal_thread_exit(phal_tid *tid);

// Called after the thread exited, to free up any potential resources
int phal_thread_destroy(phal_tid *tid);
void **phal_get_tls();

int phal_semaphore_create(phal_semaphore *sem);
int phal_semaphore_destroy(phal_semaphore *sem);

/// Lock the semaphore.
int phal_semaphore_lock(phal_semaphore *sem);
int phal_semaphore_unlock(phal_semaphore *sem);

int phal_semaphore_signal(phal_semaphore *sem);
int phal_semaphore_broadcast(phal_semaphore *sem);

/// Wait for the semaphore to be signaled. Note that we should **not** wake up
/// if a signal was previously sent. This is not a counting semaphore.
/// This should be called with the semaphore locked ! It will unlock the
/// semaphore when it goes to sleep, and lock it when it wakes up. The lock must
/// also be held when signaling/broadcasting the semaphore. This prevents race
/// conditions from occuring.
int phal_semaphore_wait(phal_semaphore *sem, const struct timespec *abs);

// TODO: pass timespec instead
int phal_thread_sleep(uint64_t msec);
