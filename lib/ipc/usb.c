#include<libtransistor/ipc/usb.h>

#include<libtransistor/types.h>
#include<libtransistor/encoding.h>
#include<libtransistor/environment.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc_helpers.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/ipc/sm.h>

#include<assert.h>

static_assert(sizeof(usb_device_data_t) == 0x66, "sizeof(usb_device_data_t) should be 0x66");
static_assert(sizeof(usb_ds_state_t) == sizeof(uint32_t), "usb_ds_state should be uint32_t");
static_assert(sizeof(usb_interface_descriptor_t) == 0x9, "sizeof(usb_interface_descriptor_t) should be 0x9");
static_assert(sizeof(usb_endpoint_descriptor_t) == 0x7, "sizeof(usb_endpoint_descriptor_t) should be 0x7");

static ipc_domain_t ds_domain;
static ipc_object_t idss_object; // nn::usb::ds::IDsService
static uint32_t ds_complex;
static uint8_t ds_next_interface_id = 0;
static usb_device_data_t *ds_current_device_data = NULL;
static kernel_version_t kernel_version = KERNEL_VERSION_INVALID;

uint8_t _usb_next_in_ep_number;
uint8_t _usb_next_out_ep_number;

static int usb_ds_initializations = 0;

static usb_device_data_t default_device_data = {
	.id_vendor = 0x1209, // https://github.com/pidcodes/pidcodes.github.com/pull/313
	.id_product = 0x8b00,
	.bcd_device = 0x0100,
	.manufacturer = "ReSwitched",
	.product = "TransistorUSB",
	.serial_number = "SerialNumber",
};

_usb_speed_info_t _usb_speed_info[] = {{1, 0x110, 2}, {1, 0x200, 3}, {1, 0x300, 4}, {0, 0, 0}};

static int ds_disable_holds = 0;
static result_t usb_ds_500_add_string_descriptor_utf8(const char *string, uint8_t *index);
static result_t usb_ds_500_add_string_descriptor_utf16(const trn_char16_t *string, ssize_t length, uint8_t *index);
static result_t usb_ds_set_device_data(usb_device_data_t *device_data);

usb_interface_descriptor_t usb_default_interface_descriptor = {
	.bLength = 0x9,
	.bDescriptorType = TRN_USB_DT_INTERFACE,
	.bInterfaceNumber = USB_DS_INTERFACE_NUMBER_AUTO,
	.bAlternateSetting = 0x00,
	.bNumEndpoints = 0x01,
	.bInterfaceClass = 0xff,
	.bInterfaceSubClass = 0xff,
	.bInterfaceProtocol = 0xff,
	.iInterface = 1
};

result_t usb_ds_init(uint32_t complex_id, usb_device_data_t *device_data) {
	if(usb_ds_initializations++ > 0) {
		if(ds_complex != complex_id) {
			return LIBTRANSISTOR_ERR_USB_ALREADY_BOUND_OTHER_COMPLEX;
		}
		if(device_data != NULL && device_data != ds_current_device_data) {
			usb_ds_set_device_data(device_data);
		}
		return RESULT_OK;
	}

	kernel_version = env_get_kernel_version();
	ds_complex = complex_id;
	ds_current_device_data = NULL;
	ds_next_interface_id = 0;
	_usb_next_in_ep_number = 1;
	_usb_next_out_ep_number = 1;

	
	result_t r;
	r = sm_init();
	if(r) {
		goto fail;
	}

	r = sm_get_service(&idss_object, "usb:ds");
	if(r) {
		goto fail_sm;
	}

	r = ipc_convert_to_domain(&idss_object, &ds_domain);
	if(r) {
		goto fail_ds_domain;
	}

	{
		ipc_request_t rq = ipc_make_request(0);
		ipc_msg_raw_data_from_value(rq, complex_id);

		// BindDevice
		r = ipc_send(idss_object, &rq, &ipc_default_response_fmt);
		if(r) {
			goto fail_ds_domain;
		}
	}

	{
		ipc_request_t rq = ipc_make_request(1);
		process_h proc = 0xffff8001;
		ipc_msg_copy_handle_from_value(rq, proc);

		// BindClientProcess
		r = ipc_send(idss_object, &rq, &ipc_default_response_fmt);
		if(r) {
			goto fail_ds_domain;
		}
	}

	if(kernel_version >= KERNEL_VERSION_500) {
		{
			ipc_request_t rq = ipc_make_request(5);
			
			// ClearDeviceData
			r = ipc_send(idss_object, &rq, &ipc_default_response_fmt);
			if(r) {
				goto fail_ds_domain;
			}
		}

		{
			// add the language string descriptor
			uint8_t index;
			uint16_t data = 0x409;
			r = usb_ds_500_add_string_descriptor_utf16((trn_char16_t*) &data, 2, &index);
			if(r) {
				goto fail_ds_domain;
			}
		}
	}

	if(device_data == NULL) {
		device_data = &default_device_data;
	}

	if((r = usb_ds_set_device_data(device_data)) != RESULT_OK) {
		goto fail_ds_domain;
	}

	// TODO: set BOS on 5.0.0+ ?
	
	sm_finalize();

	return RESULT_OK;

fail_ds_domain:
	ipc_close_domain(ds_domain);
fail_sm:
	sm_finalize();
fail:
	usb_ds_initializations--;
	return r;
}

static result_t usb_ds_500_add_string_descriptor_utf8(const char *string, uint8_t *index) {
	trn_char16_t string16[0x40];

	if(trn_utf8_to_utf16(string16, string, sizeof(string16)/sizeof(trn_char16_t)) == NULL) {
		return LIBTRANSISTOR_ERR_INVALID_ARGUMENT;
	}

	size_t size;
	for(size = 0; string16[size] != 0; size++) { }

	return usb_ds_500_add_string_descriptor_utf16(string16, size * 2, index);
}

static result_t usb_ds_500_add_string_descriptor_utf16(const trn_char16_t *string, ssize_t length, uint8_t *index) {
	usb_string_descriptor_t descriptor;
	
	if(length < 0) {
		length = strlen(string);
	}
	if((size_t) length > sizeof(descriptor.bString)) {
		return LIBTRANSISTOR_ERR_INVALID_ARGUMENT;
	}
	descriptor.bLength = length + 2;
	descriptor.bDescriptorType = TRN_USB_DT_STRING;
	memcpy(descriptor.bString, string, length);

	ipc_buffer_t buffers[] = {ipc_buffer_from_value(descriptor, 5)};
	
	ipc_request_t rq = ipc_make_request(6);
	ipc_msg_set_buffers(rq, buffers, buffer_ptrs);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, index);
	
	return ipc_send(idss_object, &rq, &rs);
}

static result_t usb_ds_set_device_data(usb_device_data_t *device_data) {
	INITIALIZATION_GUARD(usb_ds);

	result_t r;

	if(kernel_version >= KERNEL_VERSION_500) {
		uint8_t iManu, iProduct, iSerial;

		LIB_ASSERT_OK(fail, usb_ds_500_add_string_descriptor_utf8(device_data->manufacturer, &iManu));
		LIB_ASSERT_OK(fail, usb_ds_500_add_string_descriptor_utf8(device_data->product, &iProduct));
		LIB_ASSERT_OK(fail, usb_ds_500_add_string_descriptor_utf8(device_data->serial_number, &iSerial));

		for(size_t i = 0; _usb_speed_info[i].valid; i++) {
			usb_device_descriptor_t descriptor = {
				.bLength = sizeof(descriptor),
				.bDescriptorType = TRN_USB_DT_DEVICE,
				.bcdUSB = _usb_speed_info[i].bcdUSB,
				.bDeviceClass = 0,
				.bDeviceSubClass = 0,
				.bDeviceProtocol = 0,
				.bMaxPacketSize = 0x40,
				.idVendor = device_data->id_vendor,
				.idProduct = device_data->id_product,
				.bcdDevice = device_data->bcd_device,
				.iManufacturer = iManu,
				.iProduct = iProduct,
				.iSerialNumber = iSerial,
				.bNumConfigurations = 1,
			};

			uint32_t speed_mode = _usb_speed_info[i].speed_mode;
			
			// SetUsbDeviceDescriptor
			ipc_request_t rq = ipc_make_request(8);
			ipc_buffer_t buffers[] = {ipc_buffer_from_value(descriptor, 5)};
			ipc_msg_set_buffers(rq, buffers, buffer_ptrs);
			ipc_msg_raw_data_from_value(rq, speed_mode);

			LIB_ASSERT_OK(fail, ipc_send(idss_object, &rq, &ipc_default_response_fmt));
		}

		ds_current_device_data = device_data;
		return RESULT_OK;
	} else {
		if(kernel_version >= KERNEL_VERSION_200) {
			ipc_buffer_t buffers[] = {ipc_buffer_from_reference(device_data, 5)};
			
			ipc_request_t rq = ipc_make_request(5);
			ipc_msg_set_buffers(rq, buffers, buffer_ptrs);

			LIB_ASSERT_OK(fail, ipc_send(idss_object, &rq, &ipc_default_response_fmt));
			
			ds_current_device_data = device_data;
			return RESULT_OK;
		} else {
			ds_current_device_data = device_data;
			return RESULT_OK; // ignore...
		}
	}
fail:
	return r;
}

result_t _usb_ds_500_append_configuration_data(usb_ds_interface_t *interface, uint32_t speed_mode, usb_descriptor_t *descriptor) {
	ipc_request_t rq = ipc_make_request(12);
	struct {
		uint8_t interface_number;
		uint32_t speed_mode;
	} raw;
	raw.interface_number = interface->interface_id;
	raw.speed_mode = speed_mode;
	ipc_msg_raw_data_from_value(rq, raw);
	
	ipc_buffer_t buffers[] = {ipc_make_buffer(descriptor, descriptor->bLength, 5)};
	ipc_msg_set_buffers(rq, buffers, buffer_ptrs);
	
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	return ipc_send(interface->object, &rq, &rs);
}

result_t usb_ds_get_interface(usb_interface_descriptor_t *descriptor, const char *name, usb_ds_interface_t *out) {
	INITIALIZATION_GUARD(usb_ds);

	out->is_enabled = false;

	if(kernel_version >= KERNEL_VERSION_500) {
		result_t r;

		LIB_ASSERT_OK(fail, _usb_ds_disable());
		
		if(descriptor->bInterfaceNumber == USB_DS_INTERFACE_NUMBER_AUTO) {
			descriptor->bInterfaceNumber = ds_next_interface_id++;
		}
		out->interface_id = descriptor->bInterfaceNumber;
		
		// RegisterInterface
		ipc_request_t rq = ipc_make_request(2);
		ipc_msg_raw_data_from_value(rq, out->interface_id);

		ipc_response_fmt_t rs = ipc_default_response_fmt;
		rs.num_objects = 1;
		rs.objects = &(out->object);

		LIB_ASSERT_OK(fail_disable, ipc_send(idss_object, &rq, &rs));

		// i < _usb_speed_info[i].valid
		for(size_t i = 0; _usb_speed_info[i].valid; i++) {
			LIB_ASSERT_OK(fail_interface, _usb_ds_500_append_configuration_data(out, _usb_speed_info[i].speed_mode, (usb_descriptor_t*) descriptor));
		}

		return RESULT_OK;
		
	fail_interface:
		ipc_close(out->object);
	fail_disable:
		_usb_ds_enable();
	fail:
		return r;
	} else {
		ipc_buffer_t buffers[] = {
			ipc_buffer_from_reference(descriptor, 5),
			ipc_buffer_from_string(name, 5)
		};
		
		ipc_request_t rq = ipc_make_request(2);
		ipc_msg_set_buffers(rq, buffers, buffer_ptrs);
		
		uint8_t raw;
		
		ipc_response_fmt_t rs = ipc_default_response_fmt;
		rs.num_objects = 1;
		rs.objects = &(out->object);
		ipc_msg_raw_data_from_value(rs, raw);
	
		return ipc_send(idss_object, &rq, &rs);
	}
}

result_t usb_ds_get_state_change_event(revent_h *event) {
	INITIALIZATION_GUARD(usb_ds);

	ipc_request_t rq = ipc_make_request(3);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_copy_handle_from_reference(rs, event);

	return ipc_send(idss_object, &rq, &rs);
}

result_t usb_ds_get_state(usb_ds_state_t *state) {
	INITIALIZATION_GUARD(usb_ds);

	ipc_request_t rq = ipc_make_request(4);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, state);

	return ipc_send(idss_object, &rq, &rs);
}

result_t _usb_ds_enable() {
	INITIALIZATION_GUARD(usb_ds);

	if(--ds_disable_holds == 0) {
		if(kernel_version >= KERNEL_VERSION_500) {
			ipc_request_t rq = ipc_make_request(10);
			return ipc_send(idss_object, &rq, &ipc_default_response_fmt);
		}
	}
	return RESULT_OK;
}

result_t _usb_ds_disable() {
	INITIALIZATION_GUARD(usb_ds);

	if(ds_disable_holds++ == 0) {
		if(kernel_version >= KERNEL_VERSION_500) {
			ipc_request_t rq = ipc_make_request(11);
			return ipc_send(idss_object, &rq, &ipc_default_response_fmt);
		}
	}
	return RESULT_OK;
}

static void usb_ds_force_finalize() {
	ipc_close(idss_object);
	ipc_close_domain(ds_domain);
	usb_ds_initializations = 0;
}

void usb_ds_finalize() {
	if(--usb_ds_initializations == 0) {
		usb_ds_force_finalize();
	}
}

static __attribute__((destructor)) void usb_destruct() {
	if(usb_ds_initializations > 0) {
		usb_ds_force_finalize();
	}
}
