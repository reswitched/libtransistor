#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/hid.h>
#include<libtransistor/hid.h>

#include<stdlib.h>
#include<string.h>
#include<malloc.h>

static bool hid_initialized = false;
static shared_memory_h shared_memory_handle;
static hid_shared_memory_t *shared_memory;

#define SHARED_MEMORY_SIZE 0x40000

result_t hid_init() {
  if(hid_initialized) {
    return RESULT_OK;
  }

  // these would be much better off if I could catch them at compile-time
  if(offsetof(hid_shared_memory_t, unknown7) != 0x5000) {
    dbg_printf("bad unknown5 offset: 0x%x", offsetof(hid_shared_memory_t, unknown5));
    return LIBTRANSISTOR_ERR_HID_BAD_STRUCTURE;
  }
  if(offsetof(hid_shared_memory_t, controllers) != 0x9A00) {
    dbg_printf("bad controllers offset: 0x%x", offsetof(hid_shared_memory_t, controllers));
    return LIBTRANSISTOR_ERR_HID_BAD_STRUCTURE;
  }
  if(sizeof(hid_controller_state_entry_t) != 0x30) {
    dbg_printf("bad state entry size");
    return LIBTRANSISTOR_ERR_HID_BAD_STRUCTURE;
  }
  if(sizeof(hid_controller_state_t) != (0x20 + (0x30 * 17))) {
    dbg_printf("bad state size");
    return LIBTRANSISTOR_ERR_HID_BAD_STRUCTURE;
  }
  if(offsetof(hid_controller_t, main) != 0x1408) {
    dbg_printf("bad main offset: 0x%x", offsetof(hid_controller_t, main));
    return LIBTRANSISTOR_ERR_HID_BAD_STRUCTURE;
  }
  if(sizeof(hid_controller_t) != 0x5000) {
    dbg_printf("bad controller size: 0x%x", sizeof(hid_controller_t));
    return LIBTRANSISTOR_ERR_HID_BAD_STRUCTURE;
  }
  
  result_t r;
  if((r = hid_ipc_init()) != RESULT_OK) {
    goto fail_no_ipc;
  }

  if((r = hid_ipc_get_shared_memory_handle(&shared_memory_handle)) != RESULT_OK) {
    goto fail_ipc;
  }

  // find a suitable address for mapping the shared memory
  uint64_t addr;
  memory_info_t memory_info;
  uint32_t page_info;
  do {
    addr = rand() << 32 | rand();
    addr+= 0x80000000;
    addr&= 0x0000007FFFFFF000;
    if((r = svcQueryMemory(&memory_info, &page_info, (void*) addr)) != RESULT_OK) {
      goto fail_shared_memory_obtained;
    }
  } while(memory_info.memory_type != 0 || memory_info.memory_attribute != 0 || memory_info.permission != 0);

  shared_memory = (hid_shared_memory_t*) addr;
  
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
