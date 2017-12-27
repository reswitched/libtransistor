#pragma once

#include<libtransistor/types.h>

result_t bpc_init();

// should never return RESULT_OK
result_t bpc_shutdown_system();

// should never return RESULT_OK
result_t bpc_reboot_system();

void bpc_finalize();
