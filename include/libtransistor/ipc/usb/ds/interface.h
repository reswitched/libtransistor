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

extern usb_interface_descriptor_t usb_default_interface_descriptor;

typedef struct {
	ipc_object_t object;
	uint8_t interface_id;
	uint8_t next_in_ep_addr;
	uint8_t next_out_ep_addr;
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

/**
 * @brief Submits a buffer for transfer over the control input endpoint
 */
result_t usb_ds_ctrl_in_post_buffer_async(usb_ds_interface_t *intf, void *buffer, size_t size, uint32_t *urb_id);

/**
 * @brief Submits a buffer for transfer over the control output endpoint
 */
result_t usb_ds_ctrl_out_post_buffer_async(usb_ds_interface_t *intf, void *buffer, size_t size, uint32_t *urb_id);

/**
 * @brief Gets an event that is signalled when a transaction completes on the control input endpoint
 */
result_t usb_ds_get_ctrl_in_completion_event(usb_ds_interface_t *intf, revent_h *event);

/**
 * @brief Gets report data for the control input endpoint
 */
result_t usb_ds_get_ctrl_in_report_data(usb_ds_interface_t *intf, usb_ds_report_t *report);

/**
 * @brief Gets an event that is signalled when a transaction completes on the control output endpoint
 */
result_t usb_ds_get_ctrl_out_completion_event(usb_ds_interface_t *intf, revent_h *event);

/**
 * @brief Gets report data for the control output endpoint
 */
result_t usb_ds_get_ctrl_out_report_data(usb_ds_interface_t *intf, usb_ds_report_t *report);

/**
 * @brief Stalls control endpoints
 */
result_t usb_ds_stall_ctrl(usb_ds_interface_t *intf);

#ifdef __cplusplus
}
#endif
