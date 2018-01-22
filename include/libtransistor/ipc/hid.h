/**
 * @file libtransistor/ipc/hid.h
 * @brief Human Interface Device IPC bindings
 */

#pragma once

#include<libtransistor/types.h>

/**
* @brief Initialize HID IPC bindings
*/
result_t hid_ipc_init();

/**
* @brief Get the handle for HID shared memory
*/
result_t hid_ipc_get_shared_memory_handle(shared_memory_h *handle);

/**
* @brief Finalize HID IPC bindings
*/
void hid_ipc_finalize();
