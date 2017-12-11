#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/nifm.h>
#include<libtransistor/ipc/sm.h>

static ipc_object_t nifm_g_object;

result_t nifm_init() {
	result_t r;
	ipc_object_t nifm_s_object;
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	r = sm_get_service(&nifm_s_object, "nifm:s");
	if(r)
		return r;

	rq.request_id = 4;
	rs.num_objects = 1;
	rs.objects = &nifm_g_object;
	nifm_g_object.object_id = -1;

	r = ipc_send(nifm_s_object, &rq, &rs);
	if(r)
	{
		ipc_close(nifm_s_object);
		return r;
	}

	ipc_close(nifm_s_object);
	return 0;
}

result_t nifm_get_ip_address(u32 *ip) {
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	rq.request_id = 12;
	rs.raw_data = ip;
	rs.raw_data_size = sizeof(*ip);

	return ipc_send(nifm_g_object, &rq, &rs);
}

void nifm_finalize() {
	ipc_close(nifm_g_object);
}
