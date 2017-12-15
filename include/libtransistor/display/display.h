#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/surface.h>

typedef struct {
	uint64_t id;
} display_t;

result_t display_init();
result_t display_open_layer(surface_t *surface);
void display_finalize();
