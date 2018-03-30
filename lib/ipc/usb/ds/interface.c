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

result_t usb_ds_interface_get_endpoint(usb_ds_interface_t *intf, usb_endpoint_descriptor_t *descriptor, usb_ds_endpoint_t *endpoint) {
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

result_t usb_ds_interface_enable(usb_ds_interface_t *intf) {
	ipc_request_t rq = ipc_make_request(3);
	return ipc_send(intf->object, &rq, &ipc_default_response_fmt);
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
