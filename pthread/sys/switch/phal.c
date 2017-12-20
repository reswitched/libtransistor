#include <pthread.h>
#include <libtransistor/nx.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdatomic.h>
#include <errno.h>
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
	int ret;
	void *stack = malloc(0x2000);
	if (stack == NULL)
		return ENOMEM;
	stack += 0x2000;
	ret = svcCreateThread(tid, start_routine, (uint64_t)arg, stack, 0x1F, -2);
	if (ret)
		return ret;
	return svcStartThread(*tid);
}

// Noreturn !
void phal_thread_exit(phal_tid *tid) {
	svcExitThread();
}

int phal_thread_destroy(phal_tid *tid) {
	return svcCloseHandle(*tid);
}

int phal_thread_sleep(uint64_t msec) {
	uint64_t nanos = msec * 1000 * 1000;
	return svcSleepThread(nanos);
}

int phal_semaphore_create(phal_semaphore *sem) {
	sem->lock = 0;
	sem->sem = 0;
	return 0;
}

int phal_semaphore_destroy(phal_semaphore *sem) { return 0; }

/// Wake up one thread waiting for the semaphore.
int phal_semaphore_signal(phal_semaphore *sem) {
	int ret;
	if ((ret = result_to_errno(svcSignalProcessWideKey(&sem->sem, 1))) != 0)
		return ret;

	// Avoid the kernel's "pre-signaling" support. This should only be
	// called with the associated mutex locked, so this is safe.
	sem->sem = 0;
	return ret;
}

int phal_semaphore_broadcast(phal_semaphore *sem) {
	int ret;
	if ((ret = phal_semaphore_lock(sem)) != 0)
		return ret;
	if ((ret = result_to_errno(svcSignalProcessWideKey(&sem->sem, 1))) != 0)
		return ret;

	// Avoid the kernel's "pre-signaling" support. This should only be
	// called with the associated mutex locked, so this is safe.
	sem->sem = 0;
	if ((ret = phal_semaphore_unlock(sem)) != 0)
		return ret;
	return ret;
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
	uint64_t nsec = 0;
	struct timeval curtime;
	struct timespec curtimespec;
	struct timespec result;

	if (abstime) {
		gettimeofday(&curtime, NULL);
		curtimespec.tv_sec = curtime.tv_sec;
		curtimespec.tv_nsec = curtime.tv_usec * 1000;
		if (timespec_subtract(&result, abstime, &curtimespec)) {
			// Negative result, set nsec to 0
			nsec = 0;
		} else {
			nsec += result.tv_sec * 1000 * 1000 * 1000;
			nsec += result.tv_nsec;
		}
	} else {
		// No timeout, set nsec to max value.
		nsec = -1;
	}

	// Mutex must be locked at this point, otherwise shit stinks.
	pthread_t self = pthread_self();
	return result_to_errno(svcWaitProcessWideKeyAtomic(&sem->lock, &sem->sem, self->tib_tid.id, nsec));
	// At this point, lock is still locked, and still ours !
}

/*int phal_mutex_create(phal_mutex *mutex) {
	*mutex = 0;
	return 0;
}

int phal_mutex_destroy(phal_mutex *mutex) { return 0; }
*/
#define HAS_LISTENERS 0x40000000

int phal_semaphore_lock(phal_semaphore *sem) {
	pthread_t self = pthread_self();
	_Atomic(uint32_t) *mutex = &sem->lock;

	while (1) {
		uint32_t cur = 0;
		if (atomic_compare_exchange_strong(mutex, &cur, self->tib_tid)) {
			// We won the race!
			return 0;
		}

		if ((cur &~ HAS_LISTENERS) == self->tib_tid) {
			// Kernel assigned it to us!
			return 0;
		}

		if (!(cur & HAS_LISTENERS)) {
			// The flag is not set, we need to set it.
			if (!atomic_compare_exchange_strong(mutex, &cur, cur | HAS_LISTENERS)) {
				continue;
			}
		}
		svcArbitrateLock(cur &~ HAS_LISTENERS, mutex, self->tib_tid.id);
	}
}

int phal_semaphore_unlock(phal_semaphore *sem) {
	_Atomic(uint32_t) *mutex = &sem->lock;
	uint32_t old = atomic_exchange(mutex, 0);
	if (old & HAS_LISTENERS)
		svcArbitrateUnlock(mutex);
}

void **phal_get_tls() {
	return (void**)(((char*)get_tls()) + 0x1F8);
	// TODO: &get_tls()->ctx;
}
