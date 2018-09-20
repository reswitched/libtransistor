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
 * @param waiter Waiter to add callback to
 * @param handle Handle to wait on
 * @param callback Callback for when handle is signalled. Return true to keep the handle registered, false to unregister it.
 * @param data Userdata passed to callback
 * @return A \ref wait_record_t valid on success, NULL on failure.
 */
wait_record_t *waiter_add(waiter_t *waiter, handle_t handle, bool (*callback)(void *data, handle_t handle), void *data);

/**
 * @brief Adds a timed callback to the waiter.
 * @param waiter Waiter to add callback to
 * @param deadline Target time to run callback, in system ticks.
 * @param callback Callback for when deadline is hit. Return zero to unregister, or return a positive value to set another deadline.
 * @param data Userdata passed to callback
 * @return A \ref wait_record_t valid on success, NULL on failure.
 */
wait_record_t *waiter_add_deadline(waiter_t *waiter, uint64_t deadline, uint64_t (*callback)(void *data), void *data);

/**
 * @brief Adds a callback to the waiter that is signalled from another thread.
 * @param waiter Waiter to add callback to
 * @param callback Callback for when record is signalled. Return true to stay registered, or false to unregister.
 * @param data Userdata passed to callback
 *
 * Use \ref waiter_signal from another thread, and call \ref waiter_reset_signal from within the callback.
 */
wait_record_t *waiter_add_signal(waiter_t *waiter, bool (*callback)(void *data), void *data);

/**
 * @brief Marks the callback represented by this record to be called, and interrupts the waiter
 * @param record Record to signal
 *
 * It is invalid to call this function on a record not returned from \ref waiter_add_signal.
 */
void waiter_signal(waiter_t *waiter, wait_record_t *record);

/**
 * @brief Resets the signal marked by \ref waiter_signal.
 * @param record Record to rest signal
 *
 * It is invalid to call this function on a record not returned from \ref waiter_add_signal.
 */
void waiter_reset_signal(waiter_t *waiter, wait_record_t *record);

/**
 * @brief Waits for handles to signal
 */
result_t waiter_wait(waiter_t *waiter, uint64_t timeout);

/**
 * @brief Removes a record from the waiter, interrupting it.
 *
 * This function may only be called once on any particular wait record.
 */
void waiter_cancel(waiter_t *waiter, wait_record_t *record);

/**
 * @brief Destroys a waiter.
 *
 * All wait records should be cancelled before calling this function.
 */
void waiter_destroy(waiter_t *waiter);

#ifdef __cplusplus
}
#endif
