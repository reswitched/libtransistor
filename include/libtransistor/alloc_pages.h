#pragma once

#include<libtransistor/types.h>

#include<stdint.h>

void *alloc_pages(size_t min, size_t max, size_t *actual);
bool free_pages(void *pages);

result_t ap_init();
result_t ap_probe_full_address_space();
void *ap_alloc_largest(size_t *size);
void ap_dump_info();
