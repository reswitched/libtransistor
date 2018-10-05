/**
 * @file libtransistor/ipc/usb.h
 * @brief USB Services
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/encoding.h>

typedef enum {
	TRN_USB_DT_DEVICE = 0x1,
	TRN_USB_DT_CONFIGURATION = 0x2,
	TRN_USB_DT_STRING = 0x3,
	TRN_USB_DT_INTERFACE = 0x4,
	TRN_USB_DT_ENDPOINT = 0x5,
	TRN_USB_DT_BOS = 0xf,
	TRN_USB_DT_DEVICE_CAPABILITY = 0x10
} trn_usb_descriptor_type_t;

typedef enum {
	TRN_USB_BT_WIRELESS_USB_DEVICE_CAPABILITY = 1,
	TRN_USB_BT_USB_2_0_EXTENSION = 2,
	TRN_USB_BT_SS_USB_DEVICE_CAPABILITY = 3,
	TRN_USB_BT_CONTAINER_ID = 4,
} trn_usb_bos_type_t;

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


typedef struct __attribute__((packed, aligned(1))) {
	uint8_t bLength;
	uint8_t bDescriptorType;
} usb_descriptor_t;

typedef struct __attribute__((packed, aligned(1))) {
	uint8_t bLength;
	uint8_t bDescriptorType; //< must be TRN_USB_DT_DEVICE
	uint16_t bcdUSB;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t iManufacturer;
	uint8_t iProduct;
	uint8_t iSerialNumber;
	uint8_t bNumConfigurations;
} usb_device_descriptor_t;

typedef struct __attribute__((packed, aligned(1))) {
	uint8_t bLength;
	uint8_t bDescriptorType; //< must be TRN_USB_DT_CONFIGURATION
	uint16_t wTotalLength;
	uint8_t bNumInterfaces;
	uint8_t bConfigurationValue;
	uint8_t iConfiguration;
	uint8_t bmAttributes;
	uint8_t bMaxPower;
} usb_configuration_descriptor_t;

typedef struct __attribute__((packed, aligned(1))) {
	uint8_t bLength; //< must be 0x9
	uint8_t bDescriptorType; //< must be TRN_USB_DT_INTERFACE
	uint8_t bInterfaceNumber; //< 0x4 means allocate automatically
	uint8_t bAlternateSetting; //< must be 0x00
	uint8_t bNumEndpoints; //< ignored
	uint8_t bInterfaceClass; // 0xff
	uint8_t bInterfaceSubClass; // 0xff
	uint8_t bInterfaceProtocol; // 0xff
	uint8_t iInterface; //< ignored
} usb_interface_descriptor_t;

typedef struct __attribute__((packed, aligned(1))) {
	uint8_t bLength; //< must be 0x7
	uint8_t bDescriptorType; //< must be TRN_USB_DT_ENDPOINT
	uint8_t bEndpointAddress; //< actual address is automatically allocated, but direction is indicated here by \ref trn_usb_endpoint_direction_t.
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
} usb_endpoint_descriptor_t;

typedef struct __attribute__((packed, aligned(1))) {
	uint8_t bLength;
	uint8_t bDescriptorType;
	union {
		trn_char16_t bString[0x40];
		uint16_t wLANGID[0x40];
	};
} usb_string_descriptor_t;

typedef struct __attribute__((packed, aligned(1))) {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDevCapabilityType;
	uint8_t dev_capability_data[0];
} usb_bos_dev_capability_descriptor_t;

typedef struct __attribute__((packed, aligned(1))) {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t wTotalLength;
	usb_bos_dev_capability_descriptor_t capabilities[0];
} usb_bos_descriptor_t;

typedef struct {
	uint16_t id_vendor;
	uint16_t id_product;
	uint16_t bcd_device;
	char manufacturer[0x20];
	char product[0x20];
	char serial_number[0x20];
} usb_device_data_t;

typedef enum {
	USB_DS_STATE_INITIAL = 0,
	USB_DS_STATE_INIT_STARTING = 6,
	USB_DS_STATE_INIT2 = 3,
	USB_DS_STATE_INIT3 = 4,
	USB_DS_STATE_INITIALIZED = 5,
	
	USB_DS_STATE_MAX = 0xFFFFFFFF
} usb_ds_state_t;

#include<libtransistor/ipc/usb/ds/endpoint.h>
#include<libtransistor/ipc/usb/ds/interface.h>

/**
 * @brief Initialize USB-as-device services
 * @param data Device data such as vid/pid. NULL for don't care.
 */
result_t usb_ds_init(uint32_t complex_id, usb_device_data_t *data);

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
 * @brief Finalize USB as device services
 */
void usb_ds_finalize();

// private
typedef struct {
	bool valid;
	uint16_t bcdUSB;
	uint32_t speed_mode;
} _usb_speed_info_t;
extern _usb_speed_info_t _usb_speed_info[];
extern uint8_t _usb_next_in_ep_number;
extern uint8_t _usb_next_out_ep_number;

result_t _usb_ds_enable();
result_t _usb_ds_disable();
result_t _usb_ds_500_append_configuration_data(usb_ds_interface_t *interface, uint32_t speed_mode, usb_descriptor_t *descriptor);

#ifdef __cplusplus
}
#endif
