/**
 * @file libtransistor/ipc/usb/ds/interface.h
 * @brief USB-as-device interface
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/usb/ds/endpoint.h>

#define USB_DS_INTERFACE_NUMBER_AUTO 0x4

typedef struct {
	uint8_t bLength; //< must be 0x9
	uint8_t bDescriptorType; //< must be 0x4
	uint8_t bInterfaceNumber; //< 0x4 means allocate automatically
	uint8_t bAlternateSetting; //< must be 0x00
	uint8_t bNumEndpoints; //< ignored
	uint8_t bInterfaceClass; // 0xff
	uint8_t bInterfaceSubClass; // 0xff
	uint8_t bInterfaceProtocol; // 0xff
	uint8_t iInterface; //< ignored
} usb_interface_descriptor_t;

extern usb_interface_descriptor_t usb_default_interface_descriptor;

typedef struct {
	ipc_object_t object;
	bool is_enabled;
} usb_ds_interface_t;

/**
 * @brief Create a new endpoint on the given interface

 * @param intf Interface to create endpoint on
 * @param descriptor Endpoint descriptor
 * @param endpoint Output for newly created endpoint
 */
result_t usb_ds_interface_get_endpoint(usb_ds_interface_t *intf, usb_endpoint_descriptor_t *descriptor, usb_ds_endpoint_t *endpoint);

/**
 * @brief Enables the given interface for use
 */
result_t usb_ds_interface_enable(usb_ds_interface_t *intf);

/**
 * @brief Disables the given interface so it can no longer be used
 */
result_t usb_ds_interface_disable(usb_ds_interface_t *intf);

/**
 * @brief Close and destroy the given interface
 */
result_t usb_ds_close_interface(usb_ds_interface_t *intf);

#ifdef __cplusplus
}
#endif
