#pragma once

#include<libtransistor/types.h>

result_t hid_ipc_init();
result_t hid_ipc_get_shared_memory_handle(shared_memory_h *handle);
void hid_ipc_finalize();
