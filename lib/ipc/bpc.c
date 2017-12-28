#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/bpc.h>

static bool bpc_initialized = false;

static ipc_object_t ibpcm_object; // IBoardPowerControlManager

result_t bpc_init() {
	if(bpc_initialized) {
		return RESULT_OK;
	}

	result_t r;
	r = sm_get_service(&ibpcm_object, "bpc");
	if(r) {
		goto fail;
	}

	bpc_initialized = true;

	return RESULT_OK;

fail:
	return r;
}

result_t bpc_shutdown_system() {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 0;

	result_t r;
	return ipc_send(ibpcm_object, &rq, &ipc_default_response_fmt);
}

result_t bpc_reboot_system() {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;

	result_t r;
	return ipc_send(ibpcm_object, &rq, &ipc_default_response_fmt);
}

void bpc_finalize() {
	ipc_close(ibpcm_object);
	bpc_initialized = false;
}
