#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/fatal.h>

static int fatal_initializations = 0;

static ipc_object_t fatal_object;

result_t fatal_init() {
	if(fatal_initializations++ > 0) {
		return RESULT_OK;
	}

	result_t r;
	r = sm_init();
	if(r) {
		goto fail;
	}

	r = sm_get_service(&fatal_object, "fatal:u");
	if(r) {
		goto fail_sm;
	}

	sm_finalize();
	return 0;

fail_sm:
	sm_finalize();
fail:
	fatal_initializations--;
	return r;
}

result_t fatal_transition_to_fatal_error(result_t code, uint64_t unknown) {
	struct {
		uint64_t result_code;
		uint64_t unknown;
	} raw_data = {
		.result_code = code,
		.unknown = unknown
	};
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;
	rq.raw_data_size = sizeof(raw_data);
	rq.raw_data = (uint32_t*) &raw_data;
	rq.send_pid = true;

	// we actually shouldn't ever return from this
	return ipc_send(fatal_object, &rq, &ipc_default_response_fmt);
}

static void fatal_force_finalize() {
	ipc_close(fatal_object);
	fatal_initializations = 0;
}

void fatal_finalize() {
	if(--fatal_initializations == 0) {
		fatal_force_finalize();
	}
}

static __attribute__((destructor)) void fatal_destruct() {
	if(fatal_initializations > 0) {
		fatal_force_finalize();
	}
}
