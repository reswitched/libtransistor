#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>

#include<string.h>

static ipc_object_t sm_object;

static u64 str2u64(const char *str) {
	char buf[8];
	int i = 0;
	for(; i < 8; i++) {
		if(str[i] == 0) { break; }
		buf[i] = str[i];
	}
	for(; i < 8; i++) {
		buf[i] = 0;
	}
	return *(u64*) buf;
}

result_t sm_init() {
	sm_object.object_id = -1;
	return svcConnectToNamedPort(&(sm_object.session), "sm:");
}

void sm_finalize() {
	ipc_close(sm_object);
}

result_t sm_get_service(ipc_object_t *out_object, const char *name) {
	if(!sm_object.session) {
		return LIBTRANSISTOR_ERR_SM_NOT_INITIALIZED;
	}
  
	u64 service_name = str2u64(name);
  
	if(strlen(name) > 8) {
		return LIBTRANSISTOR_ERR_SM_SERVICE_NAME_TOO_LONG;
	}

	out_object->object_id = -1;
  
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;
	rq.raw_data = (u32*) &service_name;
	rq.raw_data_size = sizeof(service_name);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_move_handles = 1;
	rs.move_handles = &(out_object->session);

	return ipc_send(sm_object, &rq, &rs);
}

result_t sm_register_service(port_h *port, const char *name, uint32_t max_sessions) {
	if(!sm_object.session) {
		return LIBTRANSISTOR_ERR_SM_NOT_INITIALIZED;
	}
  
	u64 service_name = str2u64(name);
  
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
	rq.raw_data = (u32*) &params;
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
  
	u64 service_name = str2u64(name);
  
	if(strlen(name) > 8) {
		return LIBTRANSISTOR_ERR_SM_SERVICE_NAME_TOO_LONG;
	}

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 3;
	rq.raw_data = (u32*) &service_name;
	rq.raw_data_size = sizeof(service_name);

	ipc_response_fmt_t rs = ipc_default_response_fmt;

	return ipc_send(sm_object, &rq, &rs);
}
