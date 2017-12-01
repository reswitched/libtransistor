#pragma once

#include<libtransistor/types.h>

result_t sm_init();
result_t sm_get_service(ipc_object_t *session, const char *name);
void sm_finalize();
