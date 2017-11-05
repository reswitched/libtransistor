#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/display.h>
#include<libtransistor/display/surface.h>

result_t vi_init();
result_t vi_open_display(const char *name, display_t *out);
result_t vi_create_stray_layer(uint32_t unknown, display_t *display, surface_t *surface);
result_t vi_transact_parcel(int32_t handle, uint32_t transaction, uint32_t flags, void *in_parcel, size_t in_parcel_size, void *out_parcel, size_t out_parcel_size);
void vi_finalize();
