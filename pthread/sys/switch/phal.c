#include <libtransistor/nx.h>
#include <stdlib.h>
#include "phal.h"
#include <errno.h>

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

int phal_semaphore_create(phal_semaphore *sem) { return 0; }

void **phal_get_tls() {
	return ((char*)get_tls()) + 0x1F8;
	// TODO: &get_tls()->ctx;
}
