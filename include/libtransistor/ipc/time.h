#pragma once

#include<libtransistor/types.h>

result_t time_init();
result_t time_get_current_time(uint64_t *time);
result_t time_finalize();
