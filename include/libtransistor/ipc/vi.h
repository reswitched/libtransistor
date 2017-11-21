#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/display.h>
#include<libtransistor/display/surface.h>

result_t vi_init();
result_t vi_open_display(const char *name, display_t *out);
result_t vi_create_stray_layer(uint32_t unknown, display_t *display, surface_t *surface);
result_t vi_open_layer(const char *display_name, uint64_t layer_id, uint64_t aruid, surface_t *surface);
result_t vi_create_managed_layer(uint32_t unknown, display_t *display, uint64_t aruid, uint64_t *layer_id);
result_t vi_transact_parcel(int32_t handle, uint32_t transaction, uint32_t flags, void *in_parcel, size_t in_parcel_size, void *out_parcel, size_t out_parcel_size);

// imds
result_t vi_imds_set_layer_visibility(bool visible, surface_t *layer);
result_t vi_imds_set_display_layer_stack(uint32_t stack, display_t *display);
result_t vi_imds_add_to_layer_stack(uint32_t stack, surface_t *layer);
result_t vi_imds_set_conductor_layer(bool conductor, surface_t *layer);
result_t vi_imds_set_content_visibility(bool visible);

// isds
result_t vi_isds_get_z_order_count_min(surface_t *layer, int64_t *z_count_min);
result_t vi_isds_get_z_order_count_max(surface_t *layer, int64_t *z_count_max);
result_t vi_isds_get_display_logical_resolution(display_t *display, int32_t *width, int32_t *height);
result_t vi_isds_set_layer_position(float x, float y, surface_t *layer);
result_t vi_isds_set_layer_size(surface_t *layer, int64_t width, int64_t height);
result_t vi_isds_get_layer_z(surface_t *layer, int64_t *z);
result_t vi_isds_set_layer_z(surface_t *layer, int64_t z);
result_t vi_isds_set_layer_visibility(bool visible, surface_t *layer);

// iads
result_t vi_iads_set_display_enabled(bool enabled, display_t *display);
result_t vi_iads_set_layer_scaling_mode(uint32_t scaling_mode, surface_t *layer);

void vi_finalize();
