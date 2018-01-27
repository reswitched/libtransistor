#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/nifm.h>
#include<libtransistor/ipc/sm.h>

typedef struct system_clock_t {
	ipc_object_t object;
} system_clock_t;

static system_clock_t sc_user, sc_network, sc_local;

system_clock_t *time_system_clock_user;
system_clock_t *time_system_clock_network;
system_clock_t *time_system_clock_local;

static int time_initializations = 0;

static result_t open_clock(ipc_object_t *time_object, system_clock_t *clock, uint32_t request_id) {
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	
	rq.request_id = request_id;
	
	rs.num_objects = 1;
	rs.objects = &clock->object;
	
	return ipc_send(*time_object, &rq, &rs);
}

result_t time_init() {
	result_t r;
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

	if((r = open_clock(&time_object, &sc_user, 0)) != RESULT_OK) {
		goto fail_time_object;
	}
	time_system_clock_user = &sc_user;

	if((r = open_clock(&time_object, &sc_network, 1)) != RESULT_OK) {
		goto fail_clock_user;
	}
	time_system_clock_network = &sc_network;

	if((r = open_clock(&time_object, &sc_local, 4)) != RESULT_OK) {
		goto fail_clock_network;
	}
	time_system_clock_local = &sc_local;

	ipc_close(time_object);
	sm_finalize();
	return RESULT_OK;

fail_clock_network:
	ipc_close(sc_network.object);
fail_clock_user:
	ipc_close(sc_user.object);
fail_time_object:
	ipc_close(time_object);
fail_sm:
	sm_finalize();
fail:
	time_initializations--;
	return r;
}

result_t time_system_clock_get_current_time(system_clock_t *system_clock, uint64_t *time) {
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	rq.request_id = 0;
	rs.raw_data = (uint32_t*) time;
	rs.raw_data_size = sizeof(*time);

	return ipc_send(system_clock->object, &rq, &rs);
}

result_t time_system_clock_set_current_time(system_clock_t *system_clock, uint64_t time) {
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;

	rq.request_id = 1;
	rq.raw_data = (uint32_t*) &time;
	rq.raw_data_size = sizeof(time);

	return ipc_send(system_clock->object, &rq, &rs);
}

static void time_force_finalize() {
	ipc_close(sc_user.object);
	ipc_close(sc_network.object);
	ipc_close(sc_local.object);
	time_initializations = 0;
}

void time_finalize() {
	if(--time_initializations == 0) {
		time_force_finalize();
	}
}

static __attribute__((destructor)) void time_destruct() {
	if(time_initializations > 0) {
		time_force_finalize();
	}
}
