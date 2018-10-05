#include<libtransistor/ipc/usb.h>

#include<libtransistor/types.h>
#include<libtransistor/environment.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc_helpers.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/ipc/sm.h>

#include<assert.h>
#include<stdio.h> // TODO: remove

result_t usb_ds_interface_get_endpoint(usb_ds_interface_t *intf, usb_endpoint_descriptor_t *descriptor, usb_ds_endpoint_t *endpoint) {
	if(env_get_kernel_version() >= KERNEL_VERSION_500) {
		if((descriptor->bEndpointAddress & 0x80) == TRN_USB_ENDPOINT_IN) {
			descriptor->bEndpointAddress = TRN_USB_ENDPOINT_IN | _usb_next_in_ep_number++;
		} else {
			descriptor->bEndpointAddress = TRN_USB_ENDPOINT_OUT | _usb_next_out_ep_number++;
		}

		result_t r;
		
		for(size_t i = 0; _usb_speed_info[i].valid; i++) {
			LIB_ASSERT_OK(fail, _usb_ds_500_append_configuration_data(intf, _usb_speed_info[i].speed_mode, (usb_descriptor_t*) descriptor));
		}

		ipc_request_t rq = ipc_make_request(0);
		ipc_msg_raw_data_from_value(rq, descriptor->bEndpointAddress);

		ipc_response_fmt_t rs = ipc_default_response_fmt;
		rs.num_objects = 1;
		rs.objects = &(endpoint->object);

		LIB_ASSERT_OK(fail, ipc_send(intf->object, &rq, &rs));
		
		return RESULT_OK;
	fail:
		return r;
	} else {
		ipc_buffer_t buffers[] = { ipc_buffer_from_reference(descriptor, 5) };
		
		ipc_request_t rq = ipc_make_request(0);
		ipc_msg_set_buffers(rq, buffers, buffer_ptrs);
		
		uint8_t raw;
		
		ipc_response_fmt_t rs = ipc_default_response_fmt;
		rs.num_objects = 1;
		rs.objects = &(endpoint->object);
		ipc_msg_raw_data_from_value(rs, raw);
		
		return ipc_send(intf->object, &rq, &rs);
	}
}

result_t usb_ds_interface_enable(usb_ds_interface_t *intf) {
	result_t r;
	
	ipc_request_t rq = ipc_make_request(3);
	LIB_ASSERT_OK(fail, ipc_send(intf->object, &rq, &ipc_default_response_fmt));

	if(!intf->is_enabled) {
		intf->is_enabled = true;
		LIB_ASSERT_OK(fail, _usb_ds_enable());
	}
	
fail:
	return r;
}

result_t usb_ds_interface_disable(usb_ds_interface_t *intf) {
	ipc_request_t rq = ipc_make_request(4);
	return ipc_send(intf->object, &rq, &ipc_default_response_fmt);
}

result_t usb_ds_close_interface(usb_ds_interface_t *intf) {
	if(intf->is_enabled) {
		usb_ds_interface_disable(intf);
	}
	return ipc_close(intf->object);
}

result_t usb_ds_ctrl_in_post_buffer_async(usb_ds_interface_t *intf, void *buffer, size_t size, uint32_t *urb_id) {
	struct {
		uint32_t size;
		void *ptr;
	} raw;
	raw.size = size;
	raw.ptr = buffer;
	
	ipc_request_t rq = ipc_make_request(5);
	ipc_msg_raw_data_from_value(rq, raw);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, urb_id);

	return ipc_send(intf->object, &rq, &rs);
}

result_t usb_ds_ctrl_out_post_buffer_async(usb_ds_interface_t *intf, void *buffer, size_t size, uint32_t *urb_id) {
	struct {
		uint32_t size;
		void *ptr;
	} raw;
	raw.size = size;
	raw.ptr = buffer;
	
	ipc_request_t rq = ipc_make_request(6);
	ipc_msg_raw_data_from_value(rq, raw);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, urb_id);

	return ipc_send(intf->object, &rq, &rs);
}

result_t usb_ds_get_ctrl_in_completion_event(usb_ds_interface_t *intf, revent_h *event) {
	ipc_request_t rq = ipc_make_request(7);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_copy_handle_from_reference(rs, event);

	return ipc_send(intf->object, &rq, &rs);
}

result_t usb_ds_get_ctrl_in_report_data(usb_ds_interface_t *intf, usb_ds_report_t *report) {
	ipc_request_t rq = ipc_make_request(8);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, report);

	return ipc_send(intf->object, &rq, &rs);
}

result_t usb_ds_get_ctrl_out_completion_event(usb_ds_interface_t *intf, revent_h *event) {
	ipc_request_t rq = ipc_make_request(9);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_copy_handle_from_reference(rs, event);

	return ipc_send(intf->object, &rq, &rs);
}

result_t usb_ds_get_ctrl_out_report_data(usb_ds_interface_t *intf, usb_ds_report_t *report) {
	ipc_request_t rq = ipc_make_request(10);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, report);

	return ipc_send(intf->object, &rq, &rs);
}

result_t usb_ds_stall_ctrl(usb_ds_interface_t *intf) {
	ipc_request_t rq = ipc_make_request(11);
	return ipc_send(intf->object, &rq, &ipc_default_response_fmt);
}
