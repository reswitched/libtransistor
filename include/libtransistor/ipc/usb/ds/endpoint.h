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

/**
 * @brief Close and destroy the given endpoint
 */
result_t usb_ds_close_endpoint(usb_ds_endpoint_t *endp);

#ifdef __cplusplus
}
#endif
