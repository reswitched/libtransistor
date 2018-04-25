/**
 * @file libtransistor/thread.h
 * @brief Threading functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<reent.h>

typedef struct {
	thread_h handle;
	bool owns_stack;
	void *stack_bottom;
	size_t stack_size;
	void (*entry)(void *arg);
	void *arg;
	struct _reent reent;
	void *pthread;
} trn_thread_t;

/**
 * @brief Creates a new thread
 * @param thread Structure to initialize
 * @param entry Entry function for thread
 * @param arg Second argument to thread entry function
 * @param priority Priority of the newly created thread. Must be between 0x00 and 0x3F.
 * @param processor_id Which processor the newly created thread will run on. Use -2 for don't care.
 * @param stack_size Size of the stack.
 * @param stack_bottom Bottom of a pre-allocated stack. If this is NULL, a new stack will be allocated via \ref alloc_pages.
 *
 * If stack_bottom is specified, the thread will not take ownership of the stack so as not to make any assumptions about how to free it. If it is NULL, a stack will be allocated via \ref alloc_pages and will be owned by the thread.
 */
result_t trn_thread_create(trn_thread_t *thread,
                           void (*entry)(void *arg),
                           void *arg,
                           uint32_t priority,
                           int32_t processor_id,
                           size_t stack_size,
                           void *stack_bottom);

/**
 * @brief Starts the given thread
 */
result_t trn_thread_start(trn_thread_t *thread);

/**
 * @brief Waits for the given thread to exit
 * @param timeout How long to wait for the thread to exit, in nanoseconds. Use negative value for no timeout.
 * @returns RESULT_OK on successful join, 0xea01 on timeout.
 */
result_t trn_thread_join(trn_thread_t *thread, int64_t timeout);

/**
 * @brief Destroys a thread.
 * It is the caller's responsibility to ensure that a living thread is not destroyed.
 */
void trn_thread_destroy(trn_thread_t *thread);

#ifdef __cplusplus
}
#endif
