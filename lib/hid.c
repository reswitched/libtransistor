#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/hid.h>
#include<libtransistor/hid.h>

#include<string.h>
#include<malloc.h>
#include<assert.h>

static bool hid_initialized = false;
static shared_memory_h shared_memory_handle;
static hid_shared_memory_t *shared_memory;

#define SHARED_MEMORY_SIZE 0x40000

static_assert(offsetof(hid_shared_memory_t, unknown7) == 0x5000, "malformed hid struct");
static_assert(offsetof(hid_shared_memory_t, controllers) == 0x9A00, "malformed hid struct");
static_assert(sizeof(hid_controller_state_entry_t) == 0x30, "malformed hid struct");
static_assert(sizeof(hid_controller_state_t) == (0x20 + (0x30 * 17)), "malformed hid struct");
static_assert(offsetof(hid_controller_t, main) == 0x1408, "malformed hid struct");
static_assert(sizeof(hid_controller_t) == 0x5000, "malformed hid struct");

result_t hid_init() {
	if(hid_initialized) {
		return RESULT_OK;
	}
  
	result_t r;
	if((r = hid_ipc_init()) != RESULT_OK) {
		goto fail_no_ipc;
	}

	if((r = hid_ipc_get_shared_memory_handle(&shared_memory_handle)) != RESULT_OK) {
		goto fail_ipc;
	}


	if ((shared_memory = find_empty_memory_block(sizeof(hid_shared_memory_t))) == NULL) {
		goto fail_shared_memory_obtained;
	}

	if((r = svcMapSharedMemory(shared_memory_handle, shared_memory, SHARED_MEMORY_SIZE, 1)) != RESULT_OK) {
		goto fail_shared_memory_obtained;
	}

	return 0;

fail_shared_memory_obtained:
	svcCloseHandle(shared_memory_handle);
fail_ipc:
	hid_ipc_finalize();
fail_no_ipc:
	return r;
}

hid_shared_memory_t *hid_get_shared_memory() {
	return shared_memory;
}

void hid_finalize() {
	svcUnmapSharedMemory(shared_memory_handle, shared_memory, SHARED_MEMORY_SIZE);
	shared_memory = NULL;
	shared_memory_handle = 0;
	svcCloseHandle(shared_memory_handle);
	hid_ipc_finalize();
}
