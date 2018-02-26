#include<libtransistor/types.h>
#include<libtransistor/util.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/ipc/vi.h>
#include<libtransistor/display/display.h>

static display_t display;
static int display_initializations = 0;

result_t display_init() {
	if(display_initializations++ > 0) {
		return RESULT_OK;
	}
	
	result_t r;

	if((r = gpu_initialize()) != RESULT_OK) {
		goto fail;
	}

	if((r = vi_init()) != RESULT_OK) {
		goto fail_gpu;
	}
	
	if((r = vi_open_display("Default", &display)) != RESULT_OK) {
		goto fail_vi;
	}

	return RESULT_OK;

fail_vi:
	vi_finalize();
fail_gpu:
	gpu_finalize();
fail:
	display_initializations--;
	return r;
}

result_t display_open_layer(surface_t *surface) {
	INITIALIZATION_GUARD(display);
	
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
	surface_destroy(surface);
	// surface takes ownership of IGBP and layer
	return r;
fail_igbp:
	vi_adjust_refcount(igbp.igbp_binder.handle, -1, 1);
	vi_close_layer(layer_id);
fail_managed_layer:
	vi_destroy_managed_layer(layer_id);
fail:
	return r;
}

void display_close_layer(surface_t *surface) {
	INITIALIZATION_GUARD_RETURN_VOID(display);
	
	surface_destroy(surface);
	vi_adjust_refcount(surface->igbp.igbp_binder.handle, -1, 1);
	vi_close_layer(surface->layer_id);
	vi_destroy_managed_layer(surface->layer_id);
}

result_t display_get_vsync_event(revent_h *event) {
	INITIALIZATION_GUARD(display);
	
	if(display.vsync == 0) {
		result_t r;
		if((r = vi_get_display_vsync_event(&display)) != RESULT_OK) {
			return r;
		}
	}
	*event = display.vsync;
	return RESULT_OK;
}

static void display_force_finalize() {
	vi_close_display(&display);
	vi_finalize();
	gpu_finalize();
	display_initializations = 0;
}

void display_finalize() {
	if(--display_initializations == 0) {
		display_force_finalize();
	}
}

static __attribute__((destructor)) void display_destruct() {
	if(display_initializations > 0) {
		display_force_finalize();
	}
}
