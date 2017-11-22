#pragma once

#include<libtransistor/types.h>

/*
  represents resources, arguments, and values to be passed between this program and PegaSwitch or another NRO loader
 */

#define LIBTRANSISTOR_CONTEXT_VERSION 2

typedef struct {
  uint64_t version;
  size_t size; // size of this struct (additional verification)

  char *log_buffer; // out
  size_t *log_length; // out

  char **argv; // in
  uint64_t argc; // in
} libtransistor_context_t;
