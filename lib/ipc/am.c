#include<libtransistor/ipc/am.h>

#include<libtransistor/types.h>
#include<libtransistor/loader_config.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/ipc/sm.h>

#include<string.h>

static bool using_workaround = false;
static ipc_domain_t am_domain;
static ipc_object_t proxy_service_object; // nn::am::service::I{ApplicationProxy,AllSystemAppletProxies}Service
static ipc_object_t proxy_object;
static ipc_object_t isc_object; // nn::am::service::ISelfController
static ipc_object_t iwc_object; // nn::am::service::IWindowController
static int am_initializations = 0;

static result_t get_object(ipc_object_t iface, int command, ipc_object_t *out) {
	INITIALIZATION_GUARD(am);
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = command;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_objects = 1;
	rs.objects = out;

	return ipc_send(iface, &rq, &rs);
}

result_t am_init() {
	if(am_initializations++ > 0) {
		return RESULT_OK;
	}

	using_workaround = loader_config.applet_workaround_active;
	if(using_workaround) {
		return RESULT_OK;
	}
	
	result_t r;
	r = sm_init();
	if(r) {
		goto fail;
	}
	
	r = sm_get_service(&proxy_service_object, "appletAE");
	if(r) {
		goto fail_sm;
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
	if((r = get_object(proxy_object, 2, &iwc_object)) != 0) { goto fail_isc; }

	sm_finalize();
	return 0;

fail_isc:
	ipc_close(isc_object);
fail_proxy:
	ipc_close(proxy_object);
fail_proxy_service:
	ipc_close(proxy_service_object);
fail_domain:
	ipc_close_domain(am_domain);
fail_sm:
	sm_finalize();
fail:
	am_initializations--;
	return r;
}

#define NO_WORKAROUND if(using_workaround) { return LIBTRANSISTOR_ERR_AM_WORKAROUND_ACTIVE; }

result_t am_isc_create_managed_display_layer(uint64_t *layer_id) {
	INITIALIZATION_GUARD(am);
	NO_WORKAROUND;
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 40;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data = (uint32_t*) layer_id;
	rs.raw_data_size = sizeof(*layer_id);

	return ipc_send(isc_object, &rq, &rs);
}

result_t am_isc_approve_to_display() {
	INITIALIZATION_GUARD(am);
	NO_WORKAROUND;
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 51;

	ipc_response_fmt_t rs = ipc_default_response_fmt;

	return ipc_send(isc_object, &rq, &rs);
}

result_t am_iwc_get_applet_resource_user_id(aruid_t *aruid) {
	INITIALIZATION_GUARD(am);
	
	if(using_workaround) {
		*aruid = loader_config.applet_workaround_aruid;
		return RESULT_OK;
	}
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data = (uint32_t*) aruid;
	rs.raw_data_size = sizeof(*aruid);

	return ipc_send(iwc_object, &rq, &rs);
}

result_t am_iwc_acquire_foreground_rights() {
	INITIALIZATION_GUARD(am);
	NO_WORKAROUND;
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 10;

	ipc_response_fmt_t rs = ipc_default_response_fmt;

	return ipc_send(iwc_object, &rq, &rs);
}

static void am_force_finalize() {
	if(!using_workaround) {
		ipc_close(iwc_object);
		ipc_close(isc_object);
		ipc_close(proxy_object);
		ipc_close(proxy_service_object);
		ipc_close_domain(am_domain);
	}
	am_initializations = 0;
}

void am_finalize() {
	if(--am_initializations == 0) {
		am_force_finalize();
	}
}

static __attribute__((destructor)) void am_destruct() {
	if(am_initializations > 0) {
		am_force_finalize();
	}
}
