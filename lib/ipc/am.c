#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/am.h>

#include<string.h>

static ipc_domain_t am_domain;
static ipc_object_t proxy_service_object; // nn::am::service::I{ApplicationProxy,AllSystemAppletProxies}Service
static ipc_object_t proxy_object;
static ipc_object_t isc_object; // nn::am::service::ISelfController
static bool am_initialized = false;

static result_t get_object(ipc_object_t iface, int command, ipc_object_t *out) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = command;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_objects = 1;
	rs.objects = out;

	return ipc_send(iface, &rq, &rs);
}

result_t am_init() {
	if(am_initialized) {
		return RESULT_OK;
	}

	result_t r;
	r = sm_get_service(&proxy_service_object, "appletAE");
	if(r) {
		goto fail_no_service;
	}

	r = ipc_convert_to_domain(&proxy_service_object, &am_domain);
	if(r) {
		goto fail_domain;
	}

	{
		// OpenApplicationProxy
		uint64_t raw[] = {0};
		handle_t handles[] = {0xFFFF8001};
    
		ipc_request_t rq = ipc_default_request;
		rq.request_id = 200;
		rq.raw_data_size = sizeof(raw);
		rq.raw_data = (uint32_t*) raw;
		rq.send_pid = true;
		rq.num_copy_handles = 1;
		rq.copy_handles = handles;

		ipc_response_fmt_t rs = ipc_default_response_fmt;
		rs.num_objects = 1;
		rs.objects = &proxy_object;

		dbg_printf("about to open application proxy");
		r = ipc_send(proxy_service_object, &rq, &rs);
		if(r) {
			goto fail_proxy_service;
		}
		dbg_printf("opened application proxy");
	}

	if((r = get_object(proxy_object, 1, &isc_object)) != 0) { goto fail_proxy; }

	am_initialized = true;

	return 0;
  
fail_proxy:
	ipc_close(proxy_object);
fail_proxy_service:
	ipc_close(proxy_service_object);
fail_domain:
	ipc_close_domain(am_domain);
fail_no_service:
	return r;
}

void am_finalize() {
	ipc_close(isc_object);
	ipc_close(proxy_object);
	ipc_close(proxy_service_object);
	ipc_close_domain(am_domain);
}
