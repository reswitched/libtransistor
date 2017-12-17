#include<libtransistor/types.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/vi.h>
#include<libtransistor/display/display.h>

static display_t display;
static bool display_initialized = false;

result_t display_init() {
	if(display_initialized) {
		return RESULT_OK;
	}
	
	result_t r;

	if((r = gpu_initialize()) != RESULT_OK) {
		return r;
	}

	if((r = vi_init()) != RESULT_OK) {
		return r;
	}
	
	if((r = vi_open_display("Default", &display)) != RESULT_OK) {
		return r;
	}

	display_initialized = true;
	
	return RESULT_OK;
}

result_t display_open_layer(surface_t *surface) {
	result_t r;

	uint64_t layer_id;
	if((r = vi_create_managed_layer(1, &display, 0, &layer_id)) != RESULT_OK) {
		goto fail;
	}

	igbp_t igbp;
	if((r = vi_open_layer("Default", layer_id, 0, &igbp)) != RESULT_OK) {
		goto fail_managed_layer;
	}

	if((r = surface_create(surface, layer_id, igbp)) != RESULT_OK) {
		goto fail_igbp;
	}
	
	if((r = vi_iads_set_layer_scaling_mode(2, layer_id)) != RESULT_OK) {
		goto fail_surface;
	}

	uint32_t stacks[] = {0x0, 0x2, 0x4, 0x5, 0xA};
	for(int i = 0; i < ARRAY_LENGTH(stacks); i++) {
		if((r = vi_imds_add_to_layer_stack(stacks[i], layer_id)) != RESULT_OK) {
			goto fail_surface;
		}
	}

	if((r = vi_isds_set_layer_z(layer_id, 2)) != RESULT_OK) {
		goto fail_surface;
	}
	
	return RESULT_OK;

fail_surface:
	// TODO: destroy
fail_igbp:
	// TODO: destroy
fail_managed_layer:
	vi_destroy_managed_layer(layer_id);
fail:
	return r;
}

result_t display_get_vsync_event(revent_h *event) {
	if(display.vsync == 0) {
		result_t r;
		if((r = vi_get_display_vsync_event(&display)) != RESULT_OK) {
			return r;
		}
	}
	*event = display.vsync;
	return RESULT_OK;
}

void display_finalize() {
	if(display_initialized) {
		vi_close_display(&display);
	}
	display_initialized = false;
}
