#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/surface.h>

typedef struct {
	uint64_t id;
	revent_h vsync;
} display_t;

result_t display_init();
result_t display_open_layer(surface_t *surface);
result_t display_get_vsync_event(revent_h *event);
void display_finalize();
