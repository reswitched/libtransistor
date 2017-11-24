#pragma once

#include <libtransistor/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

result_t ro_init();
void ro_finalize();

result_t ro_load_nro(void **nro_base, void *nro_heap, uint64_t nro_size, void *nro_bss, uint64_t bss_size);
result_t ro_unload_nro(void *nro_base, void *nro_heap);
result_t ro_load_nrr(void *nrr_heap, uint64_t nrr_size);
result_t ro_unload_nrr(void *nrr_heap);
