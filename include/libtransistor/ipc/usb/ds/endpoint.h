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

typedef struct __attribute__((packed, aligned(1))) {
	uint8_t bLength; //< must be 0x7
	uint8_t bDescriptorType; //< must be TRN_USB_DT_ENDPOINT
	uint8_t bEndpointAddress; //< actual address is automatically allocated, but direction is indicated here by \ref trn_usb_endpoint_direction_t.
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
} usb_endpoint_descriptor_t;

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

#ifdef __cplusplus
}
#endif
