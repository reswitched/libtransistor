/**
 * @file libtransistor/waiter.h
 * @brief Manager for waiting on synchronizable handles
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

typedef struct waiter_t waiter_t;
typedef struct wait_record_t wait_record_t;

/**
 * @brief Creates a new waiter object
 */
waiter_t *waiter_create();

/**
 * @brief Adds a handle to wait on to the waiter.
 * @param water Waiter to add handle to
 * @param handle Handle to wait on
 * @param signal Callback for when handle is signalled. Return true to keep the handle registered, false to unregister it.
 * @param data Userdata passed to signal
 * @return A \ref wait_record_t valid on success, NULL on failure.
 */
wait_record_t *waiter_add(waiter_t *waiter, handle_t handle, bool (*signal)(void *data, handle_t handle), void *data);

/**
 * @brief Waits for handles to signal
 */
result_t waiter_wait(waiter_t *waiter, uint64_t timeout);

/**
 * @brief Cancels waiting.
 * It is invalid to call this on a record that has had its callback invoked and that returned false from that callback.
 */
void waiter_cancel(waiter_t *waiter, wait_record_t *record);

/**
 * @brief Destroys a waiter
 */
void waiter_destroy(waiter_t *waiter);

#ifdef __cplusplus
}
#endif
