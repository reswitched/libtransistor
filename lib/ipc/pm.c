#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/pm.h>

static int pm_initializations = 0;

static ipc_object_t ishell_object; // nn::pm::detail::IShellInterface

result_t pm_init() {
	if(pm_initializations++ > 0) {
		return RESULT_OK;
	}

	result_t r;
	r = sm_init();
	if(r) {
		goto fail;
	}

	r = sm_get_service(&ishell_object, "pm:shell");
	if(r) {
		goto fail_sm;
	}

	sm_finalize();
	return 0;

fail_sm:
	sm_finalize();
fail:
	pm_initializations--;
	return r;
}

result_t pm_terminate_process_by_title_id(uint64_t title_id) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2;
	rq.raw_data_size = sizeof(title_id);
	rq.raw_data = (uint32_t*) title_id;

	ipc_response_fmt_t rs = ipc_default_response_fmt;

	return ipc_send(ishell_object, &rq, &rs);
}

static void pm_force_finalize() {
	ipc_close(ishell_object);
	pm_initializations = 0;
}

void pm_finalize() {
	if(--pm_initializations == 0) {
		pm_force_finalize();
	}
}

static __attribute__((destructor)) void pm_destruct() {
	if(pm_initializations > 0) {
		pm_force_finalize();
	}
}
