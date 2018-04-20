#include <libtransistor/types.h>
#include <libtransistor/svc.h>
#include <libtransistor/ipc.h>
#include <libtransistor/err.h>
#include <libtransistor/util.h>
#include <libtransistor/internal_util.h>
#include <libtransistor/ipc/sm.h>
#include <libtransistor/ipc/ro.h>

#include <string.h>
#include <malloc.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static ipc_object_t ro_object;
static int ro_initializations = 0;

result_t ro_init() {
	if(ro_initializations++ > 0) {
		return RESULT_OK;
	}
	
	result_t r;
	uint64_t raw[] = {0};
	handle_t handle = 0xffff8001;
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	r = sm_init();
	if(r) {
		goto fail;
	}
	
	r = sm_get_service(&ro_object, "ldr:ro");
	if(r) {
		goto fail_sm;
	}

	if(!ro_object.is_borrowed) {
		rq.request_id = 4;
		rq.raw_data = (uint32_t*) raw;
		rq.raw_data_size = sizeof(raw);
		rq.send_pid = true;
		rq.num_copy_handles = 1;
		rq.copy_handles = &handle;
		
		r = ipc_send(ro_object, &rq, &rs);
		if(r) {
			goto fail_ro_object;
		}
	}

	sm_finalize();
	return 0;

fail_ro_object:
	ipc_close(ro_object);
fail_sm:
	sm_finalize();
fail:
	ro_initializations--;
	return r;
}

static void ro_force_finalize() {
	ipc_close(ro_object);
	ro_initializations = 0;
}

void ro_finalize() {
	if(--ro_initializations == 0) {
		ro_force_finalize();
	}
}

static __attribute__((destructor)) void ro_destruct() {
	if(ro_initializations > 0) {
		ro_force_finalize();
	}
}

result_t ro_load_nro(void **nro_base, void *nro_heap, uint64_t nro_size, void *nro_bss, uint64_t bss_size) {
	INITIALIZATION_GUARD(ro);
	
	result_t r;
	uint64_t response;
	uint64_t raw[] = {0, (uint64_t) nro_heap, nro_size, (uint64_t) nro_bss, bss_size};
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	rq.request_id = 0;
	rq.raw_data = (uint32_t*) raw;
	rq.raw_data_size = sizeof(raw);
	rq.send_pid = true;

	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) &response;

	r = ipc_send(ro_object, &rq, &rs);
	if(r) {
		return r;
	}

	*nro_base = (void*) response;

	return 0;
}

result_t ro_unload_nro(void *nro_base, void *nro_heap) {
	INITIALIZATION_GUARD(ro);

	result_t r;
	uint64_t raw[] = {0, (uint64_t) nro_base, (uint64_t) nro_heap};
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	rq.request_id = 1;
	rq.raw_data = (uint32_t*) raw;
	rq.raw_data_size = sizeof(raw);
	rq.send_pid = true;

	r = ipc_send(ro_object, &rq, &rs);
	if(r) {
		return r;
	}

	return 0;
}

result_t ro_load_nrr(void *nrr_heap, uint64_t nrr_size) {
	INITIALIZATION_GUARD(ro);
	
	result_t r;
	uint64_t raw[] = {0, (uint64_t) nrr_heap, nrr_size};
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	rq.request_id = 2;
	rq.raw_data = (uint32_t*) raw;
	rq.raw_data_size = sizeof(raw);
	rq.send_pid = true;

	r = ipc_send(ro_object, &rq, &rs);
	if(r) {
		return r;
	}

	return 0;
}

result_t ro_unload_nrr(void *nrr_heap) {
	INITIALIZATION_GUARD(ro);
	
	result_t r;
	uint64_t raw[] = {0, (uint64_t) nrr_heap};
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	rq.request_id = 3;
	rq.raw_data = (uint32_t*) raw;
	rq.raw_data_size = sizeof(raw);
	rq.send_pid = true;

	r = ipc_send(ro_object, &rq, &rs);
	if(r) {
		return r;
	}

	return 0;
}

session_h ro_get_service_handle() {
	return ro_object.session;
}
