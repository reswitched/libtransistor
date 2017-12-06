#include<libtransistor/ipcserver.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/context.h>

#include<stdio.h>
#include<malloc.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

static result_t add_object_dispatch(ipc_server_object_t *obj, ipc_message_t *msg, uint32_t rqid) {
	result_t r = 0;
	
	printf("dispatched to add_obj(%ld): %d\n", *((uint64_t*) obj->userdata), rqid);

	switch(rqid) {
	case 0: { // ADD
		uint64_t val;
		
		ipc_request_fmt_t rq = ipc_default_request_fmt;
		rq.raw_data_size = sizeof(val);
		rq.raw_data = (uint32_t*) &val;
		
		ASSERT_OK(hard_failure, ipc_unflatten_request(msg, &rq, obj));

		val+= *((uint64_t*) obj->userdata);
		
		ipc_response_t rs = ipc_default_response;
		rs.raw_data_size = sizeof(val);
		rs.raw_data = (uint32_t*) &val;

		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &rs));
		
		break; }
	default:
		r = LIBTRANSISTOR_ERR_IPCSERVER_NO_SUCH_COMMAND;
		goto hard_failure;
	}
	return RESULT_OK;

soft_failure: {
		ipc_response_t rs = ipc_default_response;
		rs.result_code = r;
		
		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &rs));
	}
hard_failure:
	return r;
}

static result_t add_object_close(ipc_server_object_t *obj) {
	free(obj->userdata);
	free(obj);
	return RESULT_OK;
}

static result_t object_dispatch(ipc_server_object_t *obj, ipc_message_t *msg, uint32_t rqid) {
	result_t r = 0;

	printf("dispatched, id: %d\n", rqid);
	
	switch(rqid) {
	case 0: { // ADD
		uint64_t val;
		
		ipc_request_fmt_t rq = ipc_default_request_fmt;
		rq.raw_data_size = sizeof(val);
		rq.raw_data = (uint32_t*) &val;
		
		ASSERT_OK(hard_failure, ipc_unflatten_request(msg, &rq, obj));

		val+= 1;
		
		ipc_response_t rs = ipc_default_response;
		rs.raw_data_size = sizeof(val);
		rs.raw_data = (uint32_t*) &val;

		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &rs));
		
		break; }
	case 1: { // CREATE_ADDER
		uint64_t val;
		
		ipc_request_fmt_t rq = ipc_default_request_fmt;
		rq.raw_data_size = sizeof(val);
		rq.raw_data = (uint32_t*) &val;
		
		ASSERT_OK(hard_failure, ipc_unflatten_request(msg, &rq, obj));
		
		ipc_server_object_t *add_obj = malloc(sizeof(*add_obj));
		if(add_obj == NULL) {
			r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
			goto soft_failure;
		}
		
		add_obj->userdata = malloc(sizeof(val));
		if(add_obj->userdata == NULL) {
			free(add_obj);
			r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
			goto soft_failure;
		}
		*(uint64_t*) add_obj->userdata = val;
		
		add_obj->dispatch = add_object_dispatch;
		add_obj->close = add_object_close;
		
		ASSERT_OK(hard_failure, ipc_server_object_register(obj, add_obj));
		
		ipc_response_t rs = ipc_default_response;
		rs.num_objects = 1;
		rs.objects = &add_obj;

		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &rs));

		break; }
	case 2: { // BUFFER_TEST
		ipc_buffer_t buffer;
		buffer.type = 0x85;
		
		ipc_buffer_t *buffers[] = {&buffer};
		
		ipc_request_fmt_t rq = ipc_default_request_fmt;
		rq.num_buffers = 1;
		rq.buffers = buffers;

		ASSERT_OK(hard_failure, ipc_unflatten_request(msg, &rq, obj));

		printf("addr: %p\n", buffer.addr);
		printf("size: %lx\n", buffer.size);
		hexdump(buffer.addr, buffer.size);
		
		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &ipc_default_response));
		break; }
	default:
		r = LIBTRANSISTOR_ERR_IPCSERVER_NO_SUCH_COMMAND;
		goto hard_failure;
	}

	return RESULT_OK;
	
soft_failure: {
		ipc_response_t rs = ipc_default_response;
		rs.result_code = r;
		
		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &rs));
	}
hard_failure:
	return r;
}

static result_t object_close(ipc_server_object_t *obj) {
	free(obj);
	return RESULT_OK;
}

static result_t object_factory(ipc_server_object_t **objptr) {
	ipc_server_object_t *obj = malloc(sizeof(*obj));
	if(obj == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	obj->userdata = NULL;
	obj->dispatch = object_dispatch;
	obj->close = object_close;
	*objptr = obj;
	return RESULT_OK;
}

port_h port;
ipc_server_t server;

void server_thread() {
	result_t r;

	printf("thread started\n");
	
	ASSERT_OK(fail_port, ipc_server_create(&server, port, object_factory));

	printf("server created\n");
	
	while(1) {
		printf("process\n");
		ASSERT_OK(fail_server, ipc_server_process(&server, 3000000000));
	}

fail_server:
	ipc_server_destroy(&server);
fail_port:
	sm_unregister_service("testsrv");
	svcCloseHandle(port);

	svcExitThread();
}

#define STACK_SIZE 0x80000

int main(int argc, char *argv[]) {
	svcSleepThread(100000000);
  
	result_t r;
	ASSERT_OK(fail, sm_init());

	ASSERT_OK(fail_sm, sm_register_service(&port, "testsrv", 20));

	thread_h thread;
	ASSERT_OK(fail_port, svcCreateThread(&thread, server_thread, 0, malloc(STACK_SIZE) + STACK_SIZE, 0x3f, -2));
	libtransistor_set_keep_loaded();
	ASSERT_OK(fail_thread, svcStartThread(thread));

	svcCloseHandle(thread);
	
	sm_finalize();

	if(libtransistor_context->magic == 0) { // mephisto
		svcExitThread();
	}
	return 0;
	
fail_server:
	ipc_server_destroy(&server);
fail_thread:
	svcCloseHandle(thread);
fail_port:
	sm_unregister_service("testsrv");
	svcCloseHandle(port);
fail_sm:
	sm_finalize();
fail:
	return r;
}
