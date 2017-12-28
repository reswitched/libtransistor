#pragma once

#include<libtransistor/types.h>

result_t nifm_init();
result_t nifm_get_ip_address(uint32_t *ip);
void nifm_finalize();
