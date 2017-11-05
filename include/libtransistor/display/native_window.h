#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/binder.h>

typedef struct {
  uint64_t layer_id;
  binder_t binder;
} native_window_t;
