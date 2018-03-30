#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc_helpers.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/usb.h>

#include<assert.h>

static_assert(sizeof(usb_descriptor_data_t) == 0x66, "sizeof(usb_descriptor_data_t) should be 0x66");
static_assert(sizeof(usb_ds_state_t) == sizeof(uint32_t), "usb_ds_state should be uint32_t");
static_assert(sizeof(usb_interface_descriptor_t) == 0x9, "sizeof(usb_interface_descriptor_t) should be 0x9");
static_assert(sizeof(usb_endpoint_descriptor_t) == 0x7, "sizeof(usb_endpoint_descriptor_t) should be 0x7");

static ipc_domain_t ds_domain;
static ipc_object_t idss_object; // nn::usb::ds::IDsService

static int usb_initializations = 0;

usb_interface_descriptor_t usb_default_interface_descriptor = {
	.bLength = 0x9,
	.bDescriptorType = TRN_USB_DT_INTERFACE,
	.bInterfaceNumber = USB_DS_INTERFACE_NUMBER_AUTO,
	.bAlternateSetting = 0x00,
	.bNumEndpoints = 0x00,
	.bInterfaceClass = 0xff,
	.bInterfaceSubClass = 0xff,
	.bInterfaceProtocol = 0xff,
	.iInterface = 0x00
};

result_t usb_init() {
	if(usb_initializations++ > 0) {
		return RESULT_OK;
	}

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

	sm_finalize();
	return RESULT_OK;

fail_ds_domain:
	ipc_close_domain(ds_domain);
fail_sm:
	sm_finalize();
fail:
	usb_initializations--;
	return r;
}

result_t usb_ds_bind_device(uint32_t complex_id) {
	INITIALIZATION_GUARD(usb);

	ipc_request_t rq = ipc_make_request(0);
	ipc_msg_raw_data_from_value(rq, complex_id);

	return ipc_send(idss_object, &rq, &ipc_default_response_fmt);
}

result_t usb_ds_bind_client_process(process_h handle) {
	INITIALIZATION_GUARD(usb);

	ipc_request_t rq = ipc_make_request(1);
	ipc_msg_copy_handle_from_value(rq, handle);

	return ipc_send(idss_object, &rq, &ipc_default_response_fmt);
}

result_t usb_ds_get_interface(usb_interface_descriptor_t *descriptor, const char *name, usb_ds_interface_t *out) {
	INITIALIZATION_GUARD(usb);

	out->is_enabled = false;
	
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

result_t usb_ds_get_state_change_event(revent_h *event) {
	INITIALIZATION_GUARD(usb);

	ipc_request_t rq = ipc_make_request(3);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_copy_handle_from_reference(rs, event);

	return ipc_send(idss_object, &rq, &rs);
}

result_t usb_ds_get_state(usb_ds_state_t *state) {
	INITIALIZATION_GUARD(usb);

	ipc_request_t rq = ipc_make_request(4);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, state);

	return ipc_send(idss_object, &rq, &rs);
}

result_t usb_ds_set_vid_pid_bcd(usb_descriptor_data_t *data) {
	INITIALIZATION_GUARD(usb);
	
	ipc_buffer_t buffers[] = {ipc_buffer_from_reference(data, 5)};

	ipc_request_t rq = ipc_make_request(5);
	ipc_msg_set_buffers(rq, buffers, buffer_ptrs);

	return ipc_send(idss_object, &rq, &ipc_default_response_fmt);
}

static void usb_force_finalize() {
	ipc_close(idss_object);
	ipc_close_domain(ds_domain);
	usb_initializations = 0;
}

void usb_finalize() {
	if(--usb_initializations == 0) {
		usb_force_finalize();
	}
}

static __attribute__((destructor)) void usb_destruct() {
	if(usb_initializations > 0) {
		usb_force_finalize();
	}
}
