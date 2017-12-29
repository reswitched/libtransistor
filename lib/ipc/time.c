#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/nifm.h>
#include<libtransistor/ipc/sm.h>

static ipc_object_t isystemclock_object;

static int time_initializations = 0;

result_t time_init() {
	result_t r;
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_object_t time_object;

	if(time_initializations++ > 0) {
		return RESULT_OK;
	}

	r = sm_init();
	if(r != RESULT_OK) {
		goto fail;
	}
	
	r = sm_get_service(&time_object, "time:s");
	if(r != RESULT_OK) {
		r = sm_get_service(&time_object, "time:g");
		if (r != RESULT_OK) {
			r = sm_get_service(&time_object, "time:a");
			if (r != RESULT_OK) {
				goto fail_sm;
			}
		}
	}

	rq.request_id = 0;
	rs.num_objects = 1;
	rs.objects = &isystemclock_object;
	r = ipc_send(time_object, &rq, &rs);

	if(r != RESULT_OK) {
		goto fail_time_object;
	}

	sm_finalize();
	ipc_close(time_object);
	return RESULT_OK;

fail_time_object:
	ipc_close(time_object);
fail_sm:
	sm_finalize();
fail:
	time_initializations--;
	return r;
}

result_t time_get_current_time(uint64_t *time) {
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	rq.request_id = 0;
	rs.raw_data = time;
	rs.raw_data_size = sizeof(*time);

	return ipc_send(isystemclock_object, &rq, &rs);
}

void time_finalize() {
	if(--time_initializations == 0) {
		ipc_close(isystemclock_object);
	}
}
