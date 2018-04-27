/**
 * @file libtransistor/ipc/usb.h
 * @brief USB Services
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/ipc/usb/ds/endpoint.h>
#include<libtransistor/ipc/usb/ds/interface.h>

typedef enum {
	TRN_USB_DT_INTERFACE = 0x4,
	TRN_USB_DT_ENDPOINT = 0x5,
} trn_usb_descriptor_type_t;

typedef enum {
	TRN_USB_ENDPOINT_OUT = 0x00,
	TRN_USB_ENDPOINT_IN = 0x80,
} trn_usb_endpoint_direction_t;

typedef enum {
	TRN_USB_TRANSFER_TYPE_CONTROL = 0x0,
	TRN_USB_TRANSFER_TYPE_ISOCHRONOUS = 0x1,
	TRN_USB_TRANSFER_TYPE_BULK = 0x2,
	TRN_USB_TRANSFER_TYPE_INTERRUPT = 0x3,
} trn_usb_transfer_type_t;

typedef struct {
	uint16_t id_vendor;
	uint16_t id_product;
	uint16_t bcd_device;
	uint8_t manufacturer[0x20];
	uint8_t product[0x20];
	uint8_t serial_number[0x20];
} usb_descriptor_data_t;

typedef enum {
	USB_DS_STATE_INITIAL = 0,
	USB_DS_STATE_INIT_STARTING = 6,
	USB_DS_STATE_INIT2 = 3,
	USB_DS_STATE_INIT3 = 4,
	USB_DS_STATE_INITIALIZED = 5,
	
	USB_DS_STATE_MAX = 0xFFFFFFFF
} usb_ds_state_t;

/**
 * @brief Initialize USB as device services
 */
result_t usb_ds_init(uint32_t complex_id);

/**
 * @brief Open a new USB interface
 * @param descriptor The descriptor for the interface to create
 * @param name Name for the interface (not sent over USB)
 * @param out Stores the newly created interface
 */
result_t usb_ds_get_interface(usb_interface_descriptor_t *descriptor, const char *name, usb_ds_interface_t *out);

/**
 * @brief Get state change event
 */
result_t usb_ds_get_state_change_event(revent_h *evt);

/**
 * @brief Get state
 */
result_t usb_ds_get_state(usb_ds_state_t *state);

/**
 * @brief Set vendor ID, product ID, and BCD
 * See http://www.beyondlogic.org/usbnutshell/usb5.shtml#DeviceDescriptors
 */
result_t usb_ds_set_vid_pid_bcd(usb_descriptor_data_t *data);

/**
 * @brief Finalize USB as device services
 */
void usb_ds_finalize();

#ifdef __cplusplus
}
#endif
