#include <pthread.h>
#include <libtransistor/nx.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdatomic.h>
#include <errno.h>
#include <string.h>
#include "thread_private.h"
#include "phal.h"

static int result_to_errno(result_t res) {
	switch (res) {
		case RESULT_OK: return 0;
		case 0xEA01: return ETIMEDOUT;
		default: return ENOSYS;
	}
}

// TODO: better error handling. Need to turn libtransistor error into unix
// errors.

int phal_thread_create(phal_tid *tid, void (*start_routine)(void*), void *arg) {
	return ENOSYS;
}

// Noreturn !
void phal_thread_exit(phal_tid *tid) {
	//svcExitThread();
}

int phal_thread_destroy(phal_tid *tid) {
	return ENOSYS;
}

int phal_thread_sleep(uint64_t msec) {
	uint64_t nanos = msec * 1000 * 1000;
	return result_to_errno(svcSleepThread(nanos));
}

int phal_semaphore_create(phal_semaphore *sem) {
	sem->lock = 0;
	sem->sem = 0;
	return 0;
}

int phal_semaphore_destroy(phal_semaphore *sem) { return 0; }

/// Wake up one thread waiting for the semaphore.
int phal_semaphore_signal(phal_semaphore *sem) {
	return ENOSYS;
}

int phal_semaphore_broadcast(phal_semaphore *sem) {
	return ENOSYS;
}

static int timespec_subtract (struct timespec *result, const struct timespec *x, struct timespec *y) {
	/* Perform the carry for the later subtraction by updating y. */
	if (x->tv_nsec < y->tv_nsec) {
		int sec = (y->tv_nsec - x->tv_nsec) / 1000 * 1000 * 1000 + 1;
		y->tv_nsec -= 1000 * 1000 * 1000 * sec;
		y->tv_sec += sec;
	}
	if (x->tv_nsec - y->tv_nsec > 1000 * 1000 * 1000) {
		int sec = (y->tv_nsec - x->tv_nsec) / 1000 * 1000 * 1000;
		y->tv_nsec += 1000 * 1000 * 1000 * sec;
		y->tv_sec -= sec;
	}

	/* Compute the time remaining to wait.
	   tv_usec is certainly positive. */
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_nsec = x->tv_nsec - y->tv_nsec;

	/* Return 1 if result is negative. */
	return x->tv_sec < y->tv_sec;
}

// TODO: This kinda sucks. Different platform behave differently here. For now
// let's focus on the switch, which needs a locked mutex and a semaphore.
/// Wait for the semaphore to be signaled. Note that we should **not** wake up
/// if a signal was previously sent. This is not a counting semaphore.
int phal_semaphore_wait(phal_semaphore *sem, const struct timespec *abstime) {
	return ENOSYS;
}

/*int phal_mutex_create(phal_mutex *mutex) {
	*mutex = 0;
	return 0;
}

int phal_mutex_destroy(phal_mutex *mutex) { return 0; }
*/
#define HAS_LISTENERS 0x40000000

int phal_semaphore_lock(phal_semaphore *sem) {
	return ENOSYS;
}

int phal_semaphore_unlock(phal_semaphore *sem) {
	return ENOSYS;
}

void **phal_get_tls() {
	trn_thread_t *thread = trn_get_thread();
	return &thread->pthread;
}
