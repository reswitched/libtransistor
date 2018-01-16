#include<libtransistor/ipcserver.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/loader_config.h>

#include<stdio.h>
#include<malloc.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

bool destroy_server_flag = false;

static void add_object_dispatch(ipc_server_object_t *obj, ipc_message_t *msg, uint32_t rqid) {
	result_t r = 0;
	
	printf("dispatched to add_obj(%ld): %d\n", *((uint64_t*) obj->userdata), rqid);
	printf("  (object session server handle: 0x%x, client handle: 0x%x\n", obj->owning_session->handle, obj->owning_session->client_handle);
	
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
	return;

soft_failure: {
		ipc_response_t rs = ipc_default_response;
		rs.result_code = r;
		
		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &rs));
	}
hard_failure:
	ipc_server_session_close(obj->owning_session);
	return;
}

static void add_object_close(ipc_server_object_t *obj) {
	free(obj->userdata);
	free(obj);
}

static void object_dispatch(ipc_server_object_t *obj, ipc_message_t *msg, uint32_t rqid) {
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

		printf("created adder object (%ld), srv: 0x%x, cli: 0x%x\n", val, add_obj->owning_session->handle, add_obj->owning_session->client_handle);
		
		ipc_response_t rs = ipc_default_response;
		rs.num_objects = 1;
		rs.objects = &add_obj;

		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &rs));

		break; }
	case 2: { // BUFFER_TEST
		ipc_buffer_t buffer;
		buffer.type = 0x5;
		
		ipc_buffer_t *buffers[] = {&buffer};
		
		ipc_request_fmt_t rq = ipc_default_request_fmt;
		rq.num_buffers = 1;
		rq.buffers = buffers;

		ASSERT_OK(hard_failure, ipc_unflatten_request(msg, &rq, obj));
		
		printf("addr: %p\n", buffer.addr);
		printf("size: %lx\n", buffer.size);

		hexdump(buffer.addr, buffer.size);
		
		uint8_t *bufu8 = buffer.addr;
		uint64_t sum = 0;
		for(size_t i = 0; i < buffer.size; i++) {
			sum+= bufu8[i];
		}
		printf("sum: %lx\n", sum);

		ipc_response_t rs = ipc_default_response;
		rs.raw_data_size = sizeof(sum);
		rs.raw_data = (uint32_t*) &sum;
		
		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &rs));
		break; }
	case 3: { // DESTROY_SERVER
		destroy_server_flag = true;
		goto hard_failure;
		break; }
	default:
		r = LIBTRANSISTOR_ERR_IPCSERVER_NO_SUCH_COMMAND;
		goto hard_failure;
	}

	return;
	
soft_failure: {
		ipc_response_t rs = ipc_default_response;
		rs.result_code = r;
		
		ASSERT_OK(hard_failure, ipc_server_object_reply(obj, &rs));
	}
hard_failure:
	printf("hard failure\n");
	ipc_server_session_close(obj->owning_session);
	return;
}

static void object_close(ipc_server_object_t *obj) {
	free(obj);
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

	destroy_server_flag = false;
	
	while(!destroy_server_flag) {
		printf("process\n");
		ASSERT_OK(fail_server, ipc_server_process(&server, 3000000000));
	}

fail_server:
	ipc_server_destroy(&server);
fail_port:
	sm_unregister_service("testsrv");

	svcExitThread();
}

#define STACK_SIZE 0x80000

ipc_object_t testsrv_object;

result_t run_simple_rawdata_test();
result_t run_object_test();
result_t run_buffer_test();

int main(int argc, char *argv[]) {
	svcSleepThread(100000000);
  
	result_t r;
	ASSERT_OK(fail, sm_init());

	ASSERT_OK(fail_sm, sm_register_service(&port, "testsrv", 20));

	thread_h thread;
	ASSERT_OK(fail_port, svcCreateThread(&thread, server_thread, 0, malloc(STACK_SIZE) + STACK_SIZE, 0x3f, -2));
	ASSERT_OK(fail_thread, svcStartThread(thread));

	ASSERT_OK(fail_sm, sm_get_service(&testsrv_object, "testsrv"));
	ASSERT_OK(fail_server, run_simple_rawdata_test());
	ASSERT_OK(fail_server, run_object_test());
	ASSERT_OK(fail_server, run_buffer_test());

fail_server:
	{ // DESTROY_SERVER
		ipc_request_t rq = ipc_default_request;
		rq.request_id = 3;

		r = ipc_send(testsrv_object, &rq, &ipc_default_response_fmt);
		if(r != 0xf601) {
			printf("DESTROY_SERVER didn't close session? 0x%x\n", r);
			r = LIBTRANSISTOR_ERR_UNSPECIFIED;
			goto fail_client;
		}
	}

	printf("waiting for server thread to terminate\n");
	uint32_t handle_index;
	ASSERT_OK(fail_client, svcWaitSynchronization(&handle_index, &thread, 1, 1000000000));
	goto fail_client;

fail_thread:
	svcCloseHandle(thread);
	// server object takes ownership of the port
fail_port:
	sm_unregister_service("testsrv");
	svcCloseHandle(port);
	goto fail_sm;

	// these resources are kept by this thread
fail_client:
	ipc_close(testsrv_object);
fail_sm:
	sm_finalize();
fail:
	return r;
}

result_t run_simple_rawdata_test() {
	result_t r;
	
	printf("=== SIMPLE RAWDATA TEST ===\n");
	for(uint64_t i = 0; i < 5; i++) {
		ipc_request_t rq = ipc_default_request;
		rq.request_id = 0;
		rq.raw_data_size = sizeof(i);
		rq.raw_data = (uint32_t*) &i;

		uint64_t outval;
		
		ipc_response_fmt_t rs = ipc_default_response_fmt;
		rs.raw_data_size = sizeof(outval);
		rs.raw_data = (uint32_t*) &outval;
		
		ASSERT_OK(fail, ipc_send(testsrv_object, &rq, &rs));

		printf("%ld => %ld\n", i, outval);
		if(outval != i + 1) {
			printf("FAILURE\n");
			return LIBTRANSISTOR_ERR_UNSPECIFIED;
		}
	}

fail:
	return r;
}

result_t run_object_test() {
	result_t r;

	printf("=== OBJECT TEST ===\n");

	for(uint64_t i = 0; i < 5; i++) {
		ipc_object_t obj;
		
		{
			ipc_request_t rq = ipc_default_request;
			rq.request_id = 1;
			rq.raw_data_size = sizeof(i);
			rq.raw_data = &i;

			ipc_response_fmt_t rs = ipc_default_response_fmt;
			rs.num_objects = 1;
			rs.objects = &obj;

			ASSERT_OK(fail, ipc_send(testsrv_object, &rq, &rs));
		}

		printf("got back object (%ld), session: 0x%x", i, obj.session);
		
		for(uint64_t j = 7; j < 12; j++) {
			ipc_request_t rq = ipc_default_request;
			rq.request_id = 0;
			rq.raw_data_size = sizeof(j);
			rq.raw_data = (uint32_t*) &j;
			
			uint64_t outval;
			
			ipc_response_fmt_t rs = ipc_default_response_fmt;
			rs.raw_data_size = sizeof(outval);
			rs.raw_data = (uint32_t*) &outval;
			
			ASSERT_OK(fail_obj, ipc_send(obj, &rq, &rs));
			
			printf("%ld [ + %ld] => %ld\n", j, i, outval);
			if(outval != i + j) {
				printf("FAILURE\n");
				return LIBTRANSISTOR_ERR_UNSPECIFIED;
			}
		}

		ipc_close(obj);
		continue;
		
	fail_obj:
		ipc_close(obj);
		goto fail;
	}

fail:
	return r;
}

result_t run_buffer_test() {
	result_t r;

	printf("=== BUFFER TEST ===\n");
	
	uint8_t data[] = {
		0xad, 0x17, 0x36, 0xc0, 0x51, 0xf9, 0x0d, 0x2f, 0xf5, 0x83, 0x3d, 0x02,
		0x01, 0xa7, 0x56, 0xd1, 0xf2, 0x87, 0x72, 0x38, 0x04, 0x21, 0xfa, 0xb3,
		0x3b, 0x96, 0x32, 0xc8, 0x20, 0xdc, 0xc4, 0xce, 0xa1, 0xcc, 0xf6, 0x69,
		0xfc, 0x14, 0xa2, 0xf9, 0x2b, 0x16, 0x6a, 0x9a, 0xf9, 0xa1, 0x15, 0x6e,
		0xc0, 0xf4, 0x50, 0x4d, 0x28, 0x47, 0x97, 0x21, 0xde, 0x8e, 0xdf, 0xe7,
		0x91, 0xdd, 0x0f, 0x79, 0x83, 0x43, 0x68, 0xee, 0xf9, 0x83, 0xcf, 0x68,
		0x40, 0x37, 0x25, 0xf1, 0xf8, 0x70, 0x2a, 0x07, 0x60, 0x9c, 0xbe, 0x99,
		0xc0, 0x1e, 0xc8, 0xb0, 0x43, 0xdc, 0xc6, 0x93, 0x50, 0xd3, 0x6d, 0x5a,
		0x5f, 0x6a, 0xc2, 0xbe, 0x91, 0xca, 0x15, 0x8e, 0x98, 0xc7, 0x1a, 0x55,
		0x23, 0xe1, 0x28, 0x14, 0xfd, 0x4a, 0x41, 0x1b, 0x97, 0x64, 0x8b, 0x7a,
		0xc2, 0xf0, 0xb1, 0xd5, 0x38, 0x0c, 0xdb, 0xc6, 0x42, 0x9f, 0xf4, 0xd0,
		0xe6, 0x69, 0x81, 0x1c, 0x42, 0xe9, 0x36, 0xad, 0x63, 0x22, 0x7d, 0x79,
		0xbb, 0xd7, 0x61, 0x2b, 0x93, 0x46, 0xc7, 0xe2, 0x15, 0x14, 0x12, 0x50,
		0x86, 0x78, 0x0a, 0x4a, 0x2f, 0x6f, 0x73, 0x48, 0xdb, 0x65, 0x9a, 0x1b,
		0x3a, 0x0d, 0x62, 0x5c, 0x2e, 0x27, 0x56, 0x85, 0xc6, 0x4c, 0xec, 0xdb,
		0x31, 0xcd, 0x01, 0x20, 0x9b, 0xd4, 0x76, 0x97, 0x3f, 0xa4, 0xeb, 0x83,
		0x10, 0xfd, 0xdd, 0xaa, 0x4e, 0xf2, 0x57, 0x02, 0xf9, 0x14, 0xf2, 0x09,
		0x87, 0x9d, 0xdb, 0xa0, 0x7a, 0x57, 0x83, 0x55, 0x7a, 0xbd, 0x25, 0xe5,
		0x11, 0x88, 0xc0, 0x42, 0xc4, 0xb5, 0x3d, 0xe7, 0xb5, 0xe9, 0x2a, 0x6f,
		0x21, 0xe2, 0x51, 0x0b, 0x21, 0xdb, 0x39, 0x79, 0x4c, 0xc6, 0xc6, 0x7b,
		0x18, 0x4c, 0x39, 0x8b, 0x76, 0xcb, 0x7b, 0x75, 0x7e, 0x93, 0xeb, 0xa3,
		0xef, 0x64, 0x50, 0xb8, 0xef, 0x13, 0x36, 0x6f, 0xd7, 0xde, 0xbf, 0xd7,
		0x7e, 0xe1, 0xcc, 0x46, 0xae, 0x9e, 0x1c, 0x46, 0xdf, 0x6e, 0xdc, 0x2c,
		0x98, 0xce, 0xda, 0xa5, 0x38, 0x15, 0x26, 0xb3, 0x8a, 0xd9, 0xf9, 0x5f,
		0xbb, 0xfd, 0xa7, 0xcc, 0x32, 0x3e, 0x0f, 0x3c, 0x78, 0x85, 0xe8, 0x78,
		0xfb, 0xac, 0x37, 0xf1, 0x3c, 0x5a, 0x78, 0x36, 0x14, 0x75, 0xe5, 0xb3,
		0x5e, 0x97, 0x3e, 0x4b, 0x9c, 0x8a, 0xa6, 0xa4, 0x82, 0x3a, 0x8c, 0xf7,
		0x70, 0x0a, 0x95, 0x72, 0xd7, 0xad, 0xfb, 0x5e, 0xf8, 0xe8, 0x73, 0x69,
		0xba, 0x80, 0x15, 0xc6, 0x0d, 0x50, 0x91, 0x0c, 0x47, 0xfe, 0x7d, 0x2a,
		0x52, 0x92, 0x8e, 0x46, 0xc2, 0xc5, 0x94, 0x87, 0x30, 0xa1, 0x2c, 0xcb,
		0x5d, 0x84, 0xe2, 0xc8, 0x7e, 0x5c, 0x59, 0xcf, 0x01, 0xd8, 0xcc, 0x56,
		0xc9, 0xab, 0x0c, 0xe0, 0x50, 0x16, 0x8c, 0xb2, 0x16, 0x2d, 0xe6, 0x3e,
		0x82, 0xc2, 0x31, 0xf8, 0x69, 0x10, 0x26, 0x76, 0x55, 0x55, 0x34, 0xc4,
		0x36, 0x1a, 0x35, 0xeb, 0x79, 0xa2, 0x7a, 0xe4, 0x4a, 0x80, 0x7e, 0x8b,
		0xff, 0x48, 0x12, 0x6e, 0x87, 0x13, 0x96, 0xb6, 0xe0, 0x84, 0x4d, 0x95,
		0xa8, 0x1d, 0x6a, 0x53, 0x2f, 0x9c, 0x0c, 0xae, 0x4f, 0x37, 0x49, 0xe4,
		0x36, 0x44, 0x42, 0x03, 0x81, 0x11, 0xb2, 0x5c, 0xbb, 0xcb, 0x83, 0x40,
		0x75, 0xce, 0x10, 0x8d, 0x41, 0x86, 0xba, 0x97, 0xd0, 0x52, 0x09, 0x58,
		0x70, 0xd7, 0xd7, 0x1e, 0x10, 0xbc, 0x1c, 0xfc, 0x8d, 0x06, 0x6c, 0xb6,
		0x78, 0x36, 0x20, 0xba, 0x9b, 0x37, 0xfb, 0x5b, 0xfe, 0x97, 0x17, 0x32,
		0x76, 0x39, 0xc3, 0x70, 0x2e, 0xfa, 0x39, 0xe7, 0xb5, 0x5f, 0x56, 0x01,
		0xaf, 0x23, 0xcc, 0x71, 0xbc, 0xd6, 0xc1, 0xf2, 0x32, 0xcf, 0x3d, 0xc4,
		0xd5, 0xe3, 0x9f, 0x16, 0xa9, 0xf7, 0x9b, 0x2f
	};
	
	ipc_buffer_t buffer;
	buffer.type = 0x5;
	buffer.addr = data;
	buffer.size = sizeof(data);

	ipc_buffer_t *buffers[] = {&buffer};

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2;
	rq.num_buffers = 1;
	rq.buffers = buffers;

	uint64_t sum = 0;
	for(size_t i = 0; i < sizeof(data); i++) {
		sum+= data[i];
	}
	printf("expecting 0x%lx\n", sum);
	
	uint64_t rsum;
	
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(rsum);
	rs.raw_data = (uint32_t*) &rsum;

	ASSERT_OK(fail, ipc_send(testsrv_object, &rq, &rs));

	printf("got 0x%lx\n", rsum);
	if(rsum != sum) {
		printf("FAILURE\n");
		return LIBTRANSISTOR_ERR_UNSPECIFIED;
	}

fail:
	return r;
}
