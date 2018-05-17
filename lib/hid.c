#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/ipc/hid.h>
#include<libtransistor/hid.h>
#include<libtransistor/address_space.h>

#include<string.h>
#include<malloc.h>
#include<assert.h>

static int hid_initializations = 0;
static shared_memory_h shared_memory_handle;
static hid_shared_memory_t *shared_memory;

static_assert(offsetof(hid_shared_memory_t, unknown7) == 0x5000, "malformed hid struct");
static_assert(offsetof(hid_shared_memory_t, controllers) == 0x9A00, "malformed hid struct");
static_assert(sizeof(hid_controller_state_entry_t) == 0x30, "malformed hid struct");
static_assert(sizeof(hid_controller_state_t) == (0x20 + (0x30 * 17)), "malformed hid struct");
static_assert(offsetof(hid_controller_t, main) == 0x1408, "malformed hid struct");
static_assert(sizeof(hid_controller_t) == 0x5000, "malformed hid struct");
static_assert(sizeof(hid_shared_memory_t) == 0x40000, "malformed hid struct");

result_t hid_init() {
	if(hid_initializations++ > 0) {
		return RESULT_OK;
	}
  
	result_t r;
	if((r = hid_ipc_init()) != RESULT_OK) {
		goto fail_no_ipc;
	}

	if((r = hid_ipc_get_shared_memory_handle(&shared_memory_handle)) != RESULT_OK) {
		goto fail_ipc;
	}


	if ((shared_memory = as_reserve(sizeof(hid_shared_memory_t))) == NULL) {
		goto fail_shared_memory_obtained;
	}

	if((r = svcMapSharedMemory(shared_memory_handle, shared_memory, sizeof(*shared_memory), 1)) != RESULT_OK) {
		goto fail_address_space_reserved;
	}

	return 0;

fail_address_space_reserved:
	as_release(shared_memory, sizeof(*shared_memory));
fail_shared_memory_obtained:
	svcCloseHandle(shared_memory_handle);
fail_ipc:
	hid_ipc_finalize();
fail_no_ipc:
	hid_initializations--;
	return r;
}

hid_shared_memory_t *hid_get_shared_memory() {
	if(hid_initializations <= 0) { return NULL; }
	return shared_memory;
}

bool hid_controller_buttons_pressed(hid_controller_t *c, hid_controller_button_mask m) {
	hid_controller_state_entry_t ent = c->main.entries[c->main.latest_idx];
	return ent.button_state & m;
}

bool hid_controller_buttons_released(hid_controller_t *c, hid_controller_button_mask m) {
	return !(hid_controller_button_pressed(c, m));
}

static void hid_force_finalize() {
	svcUnmapSharedMemory(shared_memory_handle, shared_memory, sizeof(*shared_memory));
	as_release(shared_memory, sizeof(*shared_memory));
	shared_memory = NULL;
	svcCloseHandle(shared_memory_handle);
	shared_memory_handle = 0;
	hid_ipc_finalize();
	hid_initializations = 0;
}

void hid_finalize() {
	if(--hid_initializations == 0) {
		hid_force_finalize();
	}
}

static __attribute__((destructor)) void hid_destruct() {
	if(hid_initializations > 0) {
		hid_force_finalize();
	}
}
