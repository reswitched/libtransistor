#pragma once

#include<libtransistor/types.h>

/*
  represents resources, arguments, and values to be passed between this program and PegaSwitch or another NRO loader
 */

#define LIBTRANSISTOR_CONTEXT_VERSION 2

// return flags
#define RETF_KEEP_LOADED	1	// do not unload NRO from memory
#define RETF_RUN_MEMINFO	2	// show memory map after cleanup

typedef struct {
  uint64_t version;
  size_t size; // size of this struct (additional verification)

  // version 1
  char *log_buffer; // out
  size_t *log_length; // out

  // version 2
  char **argv; // in
  uint64_t argc; // in

  // version 3
  void *mem_base; // in, usable contiguous block of free memory
  uint64_t mem_size; // in, ^ size
  int std_socket; // in, stdout socket from loader
  handle_t ro_handle; // in, ldr:ro service handle
  uint64_t return_flags; // out
} libtransistor_context_t;

extern libtransistor_context_t *libtransistor_context;

void libtransistor_set_keep_loaded();
void libtransistor_set_run_meminfo();
