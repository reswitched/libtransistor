#include<libtransistor/ipc/nifm.h>

#include<libtransistor/types.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/sm.h>

static ipc_object_t nifm_g_object;
static int nifm_initializations = 0;

result_t nifm_init() {
	if(nifm_initializations++ > 0) {
		return RESULT_OK;
	}
	
	result_t r;
	ipc_object_t nifm_s_object;
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	r = sm_init();
	if(r) {
		goto fail;
	}
	
	r = sm_get_service(&nifm_s_object, "nifm:s");
	if(r) {
		goto fail_sm;
	}

	rq.request_id = 4;
	rs.num_objects = 1;
	rs.objects = &nifm_g_object;
	nifm_g_object.object_id = -1;

	r = ipc_send(nifm_s_object, &rq, &rs);
	if(r) {
		goto fail_s_object;
	}

	ipc_close(nifm_s_object);
	sm_finalize();
	return 0;

fail_s_object:
	ipc_close(nifm_s_object);
fail_sm:
	sm_finalize();
fail:
	nifm_initializations--;
	return r;
}

result_t nifm_get_ip_address(uint32_t *ip) {
	INITIALIZATION_GUARD(nifm);
	
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	rq.request_id = 12;
	rs.raw_data = ip;
	rs.raw_data_size = sizeof(*ip);

	return ipc_send(nifm_g_object, &rq, &rs);
}

static void nifm_force_finalize() {
	ipc_close(nifm_g_object);
	nifm_initializations = 0;
}

void nifm_finalize() {
	if(--nifm_initializations == 0) {
		nifm_force_finalize();
	}
}

static __attribute__((destructor)) void nifm_destruct() {
	if(nifm_initializations > 0) {
		nifm_force_finalize();
	}
}
