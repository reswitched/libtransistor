#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/bpc.h>

static int bpc_initializations = 0;

static ipc_object_t ibpcm_object; // IBoardPowerControlManager

result_t bpc_init() {
	if(bpc_initializations++ > 0) {
		return RESULT_OK;
	}

	result_t r;
	r = sm_init();
	if(r) {
		goto fail;
	}
	
	r = sm_get_service(&ibpcm_object, "bpc");
	if(r) {
		goto fail_sm;
	}

	sm_finalize();
	return RESULT_OK;

fail_sm:
	sm_finalize();
fail:
	bpc_initializations--;
	return r;
}

result_t bpc_shutdown_system() {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 0;

	return ipc_send(ibpcm_object, &rq, &ipc_default_response_fmt);
}

result_t bpc_reboot_system() {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;

	return ipc_send(ibpcm_object, &rq, &ipc_default_response_fmt);
}

static void bpc_force_finalize() {
	ipc_close(ibpcm_object);
	bpc_initializations = 0;
}

void bpc_finalize() {
	if(--bpc_initializations == 0) {
		bpc_force_finalize();
	}
}

static __attribute__((destructor)) void bpc_destruct() {
	if(bpc_initializations > 0) {
		bpc_force_finalize();
	}
}
