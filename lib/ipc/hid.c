#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/hid.h>

#include<string.h>
#include<malloc.h>

static int hid_ipc_initializations = 0;

static ipc_object_t hid_server_object;
static ipc_object_t applet_resource_object;

result_t hid_ipc_init() {
	if(hid_ipc_initializations++ > 0) {
		return RESULT_OK;
	}

	result_t r;
	r = sm_init();
	if(r) {
		goto fail;
	}
	
	r = sm_get_service(&hid_server_object, "hid");
	if(r) {
		goto fail_sm;
	}

	{
		uint64_t raw[] = {0}; // applet resource user id
    
		ipc_request_t rq = ipc_default_request;
		rq.request_id = 0; // CreateAppletResource
		rq.send_pid = true;
		rq.raw_data_size = sizeof(raw);
		rq.raw_data = (uint32_t*) raw;

		ipc_response_fmt_t rs = ipc_default_response_fmt;
		rs.num_objects = 1;
		rs.objects = &applet_resource_object;

		r = ipc_send(hid_server_object, &rq, &rs);
		if(r) {
			goto fail_hid_server_object;
		}
	}

	sm_finalize();
	return 0;

fail_hid_server_object:
	ipc_close(hid_server_object);
fail_sm:
	sm_finalize();
fail:
	hid_ipc_initializations--;
	return r;
}

result_t hid_ipc_get_shared_memory_handle(shared_memory_h *handle) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 0;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_copy_handles = 1;
	rs.copy_handles = handle;

	return ipc_send(applet_resource_object, &rq, &rs);
}

static void hid_ipc_force_finalize() {
	ipc_close(applet_resource_object);
	ipc_close(hid_server_object);
	hid_ipc_initializations = 0;
}

void hid_ipc_finalize() {
	if(--hid_ipc_initializations == 0) {
		hid_ipc_force_finalize();
	}
}


static __attribute__((destructor)) void hid_ipc_destruct() {
	if(hid_ipc_initializations > 0) {
		hid_ipc_force_finalize();
	}
}
