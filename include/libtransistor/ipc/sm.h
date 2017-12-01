#pragma once

#include<libtransistor/types.h>

result_t sm_init();
result_t sm_get_service(ipc_object_t *session, const char *name);
result_t sm_register_service(port_h *port, const char *name, uint32_t max_sessions);
result_t sm_unregister_service(const char *name);
void sm_finalize();
