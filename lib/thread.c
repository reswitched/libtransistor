#include<libtransistor/thread.h>

#include<libtransistor/alloc_pages.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/tls.h>
#include<libtransistor/util.h>

#include<reent.h>
#include<string.h>

static void trn_thread_entry(void *data) {
	trn_thread_t *thread = data;
	get_tls()->thread = thread;
	_REENT_INIT_PTR(&thread->reent);
	thread->entry(thread->arg);
	svcExitThread();
}

result_t trn_thread_create(trn_thread_t *thread,
                           void (*entry)(void *arg),
                           void *arg,
                           uint32_t priority,
                           int32_t processor_id,
                           size_t stack_size,
                           void *stack_bottom) {
	memset(thread, 0, sizeof(*thread));
	
	result_t r;
	if(priority == -1) {
		LIB_ASSERT_OK(fail, svcGetThreadPriority(&priority, 0xffff8000));
	}

	if(stack_bottom == NULL) {
		thread->owns_stack = true;
		thread->stack_bottom = alloc_pages(stack_size, stack_size, &thread->stack_size);
		if(thread->stack_bottom == NULL) {
			return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		}
	} else {
		thread->owns_stack = false;
		thread->stack_bottom = stack_bottom;
		thread->stack_size = stack_size;
	}
	
	thread->entry = entry;
	thread->arg = arg;
	thread->pthread = NULL;

	LIB_ASSERT_OK(fail_stack, svcCreateThread(&thread->handle, &trn_thread_entry, thread, thread->stack_bottom + thread->stack_size, priority, processor_id));

	return RESULT_OK;
	
fail_stack:
	if(thread->owns_stack) {
		free_pages(thread->stack_bottom);
	}
fail:
	return r;
}

result_t trn_thread_start(trn_thread_t *thread) {
	return svcStartThread(thread->handle);
}

result_t trn_thread_join(trn_thread_t *thread, int64_t timeout) {
	result_t r;
	do {
		uint32_t index;
		if((r = svcWaitSynchronization(&index, &thread->handle, 1, timeout)) != 0xea01) {
			return r;
		}
	} while(timeout < 0);
	return 0xea01;
}

void trn_thread_destroy(trn_thread_t *thread) {
	if(thread->owns_stack) {
		free_pages(thread->stack_bottom);
	}
	svcCloseHandle(thread->handle);
}
