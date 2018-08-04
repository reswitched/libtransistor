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

static_assert(sizeof(usb_ds_report_t) == 0x84, "malformed usb_ds_report_t structure");

result_t usb_ds_post_buffer_async(usb_ds_endpoint_t *endp, void *buffer, size_t size, uint32_t *urb_id) {
	struct {
		uint32_t size;
		void *ptr;
	} raw;
	raw.size = size;
	raw.ptr = buffer;
	
	ipc_request_t rq = ipc_make_request(0);
	ipc_msg_raw_data_from_value(rq, raw);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, urb_id);

	return ipc_send(endp->object, &rq, &rs);
}

result_t usb_ds_get_completion_event(usb_ds_endpoint_t *endp, revent_h *event) {
	ipc_request_t rq = ipc_make_request(2);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_copy_handle_from_reference(rs, event);

	return ipc_send(endp->object, &rq, &rs);
}

result_t usb_ds_get_report_data(usb_ds_endpoint_t *endp, usb_ds_report_t *report) {
	ipc_request_t rq = ipc_make_request(3);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, report);

	return ipc_send(endp->object, &rq, &rs);
}

result_t usb_ds_close_endpoint(usb_ds_endpoint_t *endp) {
	return ipc_close(endp->object);
}

result_t usb_ds_stall(usb_ds_endpoint_t *endp) {
	ipc_request_t rq = ipc_make_request(4);
	return ipc_send(endp->object, &rq, &ipc_default_response_fmt);
}
