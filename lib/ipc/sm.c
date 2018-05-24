#include<libtransistor/types.h>
#include<libtransistor/loader_config.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>

#include<string.h>

static ipc_object_t sm_object;
static int sm_initializations = 0;
static bool sm_registered = false;

result_t sm_init() {
	if(sm_initializations++ > 0) {
		return RESULT_OK;
	}
  
	sm_object.object_id = -1;
	result_t r = svcConnectToNamedPort(&(sm_object.session), "sm:");
	if(r != RESULT_OK) {
		goto fail;
	}

	sm_registered = false;
	return RESULT_OK;

fail_port:
	ipc_close(sm_object);
fail:
	sm_initializations--;
	return r;
}

static void sm_force_finalize() {
	ipc_close(sm_object);
	sm_registered = false;
	sm_initializations = 0;
}

void sm_finalize() {
	if(--sm_initializations == 0) {
		sm_force_finalize();
	}
}

static __attribute__((destructor)) void sm_destruct() {
	if(sm_initializations > 0) {
		sm_force_finalize();
	}
}

static result_t sm_register() { // we only do this when necessary
	uint64_t raw = 0;
	ipc_request_t rq = ipc_default_request;
	rq.send_pid = true;
	rq.raw_data_size = sizeof(raw);
	rq.raw_data = &raw;
	
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	result_t r = ipc_send(sm_object, &rq, &rs);
	if(r == RESULT_OK) {
		sm_registered = true;
	}
	return r;
}

result_t sm_get_service(ipc_object_t *out_object, const char *name) {
	return sm_get_service_ex(out_object, name, false);
}

result_t sm_get_service_ex(ipc_object_t *out_object, const char *name, bool require_override) {
	if(!sm_object.session) {
		return LIBTRANSISTOR_ERR_SM_NOT_INITIALIZED;
	}
  
	uint64_t service_name = str2u64(name);
  
	if(strlen(name) > 8) {
		return LIBTRANSISTOR_ERR_SM_SERVICE_NAME_TOO_LONG;
	}

	out_object->object_id = -1;
	out_object->is_borrowed = false;
	
	for(int i = 0; i < loader_config.num_service_overrides; i++) {
		if(loader_config.service_overrides[i].service_name == service_name) {
			out_object->session = loader_config.service_overrides[i].service_handle;
			out_object->is_borrowed = true;
			return RESULT_OK;
		}
	}

	if(require_override) {
		return HOMEBREW_ABI_KEY_NOT_PRESENT(LCONFIG_KEY_OVERRIDE_SERVICE);
	}
  
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;
	rq.raw_data = (uint32_t*) &service_name;
	rq.raw_data_size = sizeof(service_name);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_move_handles = 1;
	rs.move_handles = &(out_object->session);

	result_t r = ipc_send(sm_object, &rq, &rs);
	if(r == 0x415 && !sm_registered) { // not initialized
		if((r = sm_register()) != RESULT_OK) {
			return r;
		}
		return sm_get_service_ex(out_object, name, require_override); // retry
	} else {
		return r;
	}
}

result_t sm_register_service(port_h *port, const char *name, uint32_t max_sessions) {
	if(!sm_object.session) {
		return LIBTRANSISTOR_ERR_SM_NOT_INITIALIZED;
	}
  
	uint64_t service_name = str2u64(name);
  
	if(strlen(name) > 8) {
		return LIBTRANSISTOR_ERR_SM_SERVICE_NAME_TOO_LONG;
	}

	// this is probably wrong
	struct {
		char service_name[8];
		uint32_t max_sessions;
		uint32_t unknown;
	} params;

	memcpy(params.service_name, &service_name, sizeof(service_name));
	params.max_sessions = max_sessions;
	params.unknown = 0x20;
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2;
	rq.raw_data = (uint32_t*) &params;
	rq.raw_data_size = sizeof(params);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_move_handles = 1;
	rs.move_handles = port;

	return ipc_send(sm_object, &rq, &rs);
}

result_t sm_unregister_service(const char *name) {
	if(!sm_object.session) {
		return LIBTRANSISTOR_ERR_SM_NOT_INITIALIZED;
	}
  
	uint64_t service_name = str2u64(name);
  
	if(strlen(name) > 8) {
		return LIBTRANSISTOR_ERR_SM_SERVICE_NAME_TOO_LONG;
	}

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 3;
	rq.raw_data = (uint32_t*) &service_name;
	rq.raw_data_size = sizeof(service_name);

	ipc_response_fmt_t rs = ipc_default_response_fmt;

	return ipc_send(sm_object, &rq, &rs);
}
