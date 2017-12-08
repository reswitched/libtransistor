#include <pthread.h>
#include <libtransistor/nx.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdatomic.h>
#include <errno.h>
#include "thread_private.h"
#include "phal.h"

// TODO: better error handling. Need to turn libtransistor error into unix
// errors.

int phal_thread_create(phal_tid *tid, void (*start_routine)(void*), void *arg) {
	int ret;
	void *stack = malloc(0x2000);
	if (stack == NULL)
		return ENOMEM;
	stack += 0x2000;
	ret = svcCreateThread(tid, start_routine, (uint64_t)arg, stack, 0, -2);
	if (ret)
		return ret;
	return svcStartThread(*tid);
}

// Noreturn !
void phal_thread_exit(phal_tid *tid) {
	svcExitThread();
}

int phal_thread_sleep(int msec) {
	return svcSleepThread(msec * 1000000);
}

int phal_semaphore_create(phal_semaphore *sem) {
	*sem = 0;
	return 0;
}

int phal_semaphore_destroy(phal_semaphore *sem) { return 0; }

int phal_semaphore_signal(phal_semaphore *sem) {
	return svcSignalProcessWideKey(sem, 1);
}

// TODO: This kinda sucks. Different platform behave differently here. For now
// let's focus on the switch, which needs a locked mutex and a semaphore.
int phal_semaphore_wait(phal_semaphore *sem, phal_mutex *m, uint64_t timeout) {
	// Mutex must be locked at this point, otherwise shit stinks.
	return svcWaitProcessWideKeyAtomic(m, sem, 1, timeout);
	// At this point, lock is still locked, and still ours !
}

int phal_mutex_create(phal_mutex *mutex) {
	*mutex = 0;
	return 0;
}

int phal_mutex_destroy(phal_mutex *mutex) { return 0; }

#define HAS_LISTENERS 0x40000000

int phal_mutex_lock(phal_mutex *mutex) {
	pthread_t self = pthread_self();

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
		svcArbitrateLock(cur &~ HAS_LISTENERS, mutex, self->tib_tid);
	}
}

int phal_mutex_unlock(phal_mutex *mutex) {
	uint32_t old = atomic_exchange(mutex, 0);
	if (old & HAS_LISTENERS)
		svcArbitrateUnlock(mutex);
}

void **phal_get_tls() {
	return (void**)(((char*)get_tls()) + 0x1F8);
	// TODO: &get_tls()->ctx;
}
