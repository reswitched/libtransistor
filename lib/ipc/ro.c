#include <libtransistor/types.h>
#include <libtransistor/svc.h>
#include <libtransistor/ipc.h>
#include <libtransistor/err.h>
#include <libtransistor/util.h>
#include <libtransistor/ipc/sm.h>
#include <libtransistor/ipc/ro.h>

#include <string.h>
#include <malloc.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static ipc_object_t ro_object;

result_t ro_init() {
	result_t r;
	uint64_t raw[] = {0};
	handle_t handle = 0xffff8001;
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	r = sm_get_service(&ro_object, "ldr:ro");
	if(r) {
		return r;
	}

	rq.request_id = 4;
	rq.raw_data = (uint32_t*) raw;
	rq.raw_data_size = sizeof(raw);
	rq.send_pid = true;
	rq.num_copy_handles = 1;
	rq.copy_handles = &handle;

	r = ipc_send(ro_object, &rq, &rs);
	if(r) {
		ipc_close(ro_object);
		return r;
	}
	
	return 0;
}

void ro_finalize() {
	ipc_close(ro_object);
}

result_t ro_load_nro(void **nro_base, void *nro_heap, uint64_t nro_size, void *nro_bss, uint64_t bss_size) {
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
