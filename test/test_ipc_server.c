#include<libtransistor/ipcserver.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>

#include<stdio.h>
#include<malloc.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

static result_t object_dispatch(ipc_server_object_t *obj, ipc_message_t *msg, uint32_t rqid) {
	result_t r;

	dbg_printf("dispatched, id: %d\n", rqid);
	
	switch(rqid) {
	case 0: {
		uint64_t val;
		ipc_request_fmt_t rq = ipc_default_request_fmt;
		rq.raw_data_size = sizeof(val);
		rq.raw_data = &val;
		
		ASSERT_OK(failure, ipc_unflatten_request(msg, &rq, obj));

		val+= 1;
		
		ipc_response_t rs = ipc_default_response;
		rs.raw_data_size = sizeof(val);
		rs.raw_data = &val;

		ASSERT_OK(failure, ipc_server_object_reply(obj, &rs));
		break; }
	failure:
	default:
		return ipc_server_session_close(obj->owning_session);
	}

	return RESULT_OK;
}

static result_t object_factory(ipc_server_object_t **objptr) {
	ipc_server_object_t *obj = malloc(sizeof(*obj));
	if(obj == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	obj->userdata = NULL;
	obj->dispatch = object_dispatch;
	*objptr = obj;
	return RESULT_OK;
}

int main(int argc, char *argv[]) {
	svcSleepThread(100000000);
  
	result_t r;
	ASSERT_OK(fail, sm_init());

	port_h port;
	ASSERT_OK(fail_sm, sm_register_service(&port, "testsrv", 20));

	ipc_server_t server;
	ASSERT_OK(fail_port, ipc_server_create(&server, port, object_factory));

	ASSERT_OK(fail_server, ipc_server_process(&server, 3000000000));

fail_server:
	ipc_server_destroy(&server);
fail_port:
	sm_unregister_service("testsrv");
	svcCloseHandle(port);
fail_sm:
	sm_finalize();
fail:
	return r;
}
