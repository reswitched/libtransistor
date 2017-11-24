#pragma once

#include<libtransistor/types.h>

result_t nifm_init();
result_t nifm_get_ip_address(u32 *ip);
void nifm_finalize();
