#pragma once

#include<libtransistor/types.h>

result_t time_init();
result_t time_get_current_time(u64 *time);
result_t time_finalize();
