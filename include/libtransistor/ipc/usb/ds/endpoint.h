/**
 * @file libtransistor/ipc/usb/ds/endpoint.h
 * @brief USB-as-device endpoint
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/ipc.h>

typedef struct {
	ipc_object_t object;
} usb_ds_endpoint_t;

typedef struct {
	uint32_t urb_id;
	uint32_t requested_size;
	uint32_t transferred_size;
	uint32_t urb_status;
} usb_ds_report_entry_t;

typedef struct {
	usb_ds_report_entry_t entries[8];
	uint32_t entry_count;
} usb_ds_report_t;

/**
 * @brief Submits the buffer for transfer over the endpoint
 */
result_t usb_ds_post_buffer_async(usb_ds_endpoint_t *endp, void *buffer, size_t size, uint32_t *urb_id);

/**
 * @brief Gets an event that is signalled when a transaction completes
 */
result_t usb_ds_get_completion_event(usb_ds_endpoint_t *endp, revent_h *event);

/**
 * @brief Gets report data
 */
result_t usb_ds_get_report_data(usb_ds_endpoint_t *endp, usb_ds_report_t *report);

/**
 * @brief Close and destroy the given endpoint
 */
result_t usb_ds_close_endpoint(usb_ds_endpoint_t *endp);

/**
 * @brief Halts an in-progress data transfer
 */
result_t usb_ds_stall(usb_ds_endpoint_t *endp);

#ifdef __cplusplus
}
#endif
