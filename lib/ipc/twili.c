#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc_helpers.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/twili.h>

#include<malloc.h>

static ipc_object_t its_object; // twili::ITwiliService
static int twili_initializations = 0;

result_t twili_init() {
	if(twili_initializations++ > 0) {
		return RESULT_OK;
	}

	result_t r;
	r = sm_init();
	if(r) {
		goto fail;
	}

	r = sm_get_service(&its_object, "twili");
	if(r) {
		goto fail_sm;
	}

	sm_finalize();
	return 0;

fail_sm:
	sm_finalize();
fail:
	twili_initializations--;
	return r;
}

static result_t twili_open_pipe(twili_pipe_t *pipe, uint32_t command_id) {
	INITIALIZATION_GUARD(twili);
	
	ipc_request_t rq = ipc_make_request(command_id);
	
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_objects = 1;
	rs.objects = &pipe->object;
	
	return ipc_send(its_object, &rq, &rs);
}

result_t twili_open_stdin(twili_pipe_t *pipe) {
	return twili_open_pipe(pipe, 0);
}

result_t twili_open_stdout(twili_pipe_t *pipe) {
	return twili_open_pipe(pipe, 1);
}

result_t twili_open_stderr(twili_pipe_t *pipe) {
	return twili_open_pipe(pipe, 2);
}

result_t twili_pipe_read(twili_pipe_t *pipe, void *buffer, size_t limit, size_t *bytes_read) {
	ipc_request_t rq = ipc_make_request(0);

	ipc_buffer_t buffers[] = {
		ipc_make_buffer(buffer, limit, 0x6),
	};
	ipc_msg_set_buffers(rq, buffers, buffer_ptrs);
	
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_msg_raw_data_from_reference(rs, bytes_read);

	return ipc_send(pipe->object, &rq, &rs);
}

result_t twili_pipe_write(twili_pipe_t *pipe, const void *buffer, size_t size) {
	ipc_request_t rq = ipc_make_request(1);

	ipc_buffer_t buffers[] = {
		ipc_make_buffer(buffer, size, 0x5),
	};
	ipc_msg_set_buffers(rq, buffers, buffer_ptrs);
	
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	return ipc_send(pipe->object, &rq, &rs);
}

static result_t twili_pipe_file_read(void *data, void *buf, size_t size, size_t *bytes_read) {
	return twili_pipe_read(data, buf, size, bytes_read);
}

static result_t twili_pipe_file_write(void *data, const void *buf, size_t size, size_t *bytes_written) {
	*bytes_written = size;
	return twili_pipe_write(data, buf, size);
}

static result_t twili_pipe_file_release(trn_file_t *file) {
	ipc_close(((twili_pipe_t*) file->data)->object);
	free(file->data);
	return RESULT_OK;
}

static trn_file_ops_t twili_pipe_fops = {
	.seek = NULL,
	.read = twili_pipe_file_read,
	.write = twili_pipe_file_write,
	.release = twili_pipe_file_release
};

int twili_pipe_fd(twili_pipe_t *pipe) {
	twili_pipe_t *pipe_copy = malloc(sizeof(*pipe_copy));
	*pipe_copy = *pipe;
	return fd_create_file(&twili_pipe_fops, pipe_copy);
}

static void twili_force_finalize() {
	ipc_close(its_object);
}

void twili_finalize() {
	if(--twili_initializations == 0) {
		twili_force_finalize();
	}
}

static __attribute__((destructor)) void twili_destruct() {
	if(twili_initializations > 0) {
		twili_force_finalize();
	}
}
