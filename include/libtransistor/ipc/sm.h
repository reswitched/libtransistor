#pragma once

#include<libtransistor/types.h>

result_t sm_init();
result_t sm_get_service(session_h *session, char *name);
void sm_finalize();
