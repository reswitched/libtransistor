#include<libtransistor/nx.h>

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "reswitched_logo.h"

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

int main() {
	svcSleepThread(100000000);
  
	result_t r;
	ASSERT_OK(fail, sm_init());
	ASSERT_OK(fail_sm, gpu_initialize());
	ASSERT_OK(fail_gpu, vi_init());
	ASSERT_OK(fail_vi, display_init());
	
	printf("initialized all modules\n");

	surface_t surf;
	ASSERT_OK(fail_display, display_open_layer(&surf));

	revent_h vsync;
	ASSERT_OK(fail_display_layer, display_get_vsync_event(&vsync));

	uint32_t *reswitched_logo_pixels = (uint32_t*) reswitched_logo_data;
	for(size_t i = 0; i < sizeof(reswitched_logo_data)/4; i++) {
		reswitched_logo_pixels[i]|= 0xFF000000; // discard alpha channel
	}
	
	for(int i = 0; i < 600; i++) {
		printf("begin frame %d\n", i);
		uint32_t *out_buffer;
		ASSERT_OK(fail_display_event, surface_dequeue_buffer(&surf, &out_buffer));
		if(i < 300) {
			ASSERT_OK(fail_display_event, surface_wait_buffer(&surf));
		}
		
		for(size_t p = 0; p < (0x3c0000/sizeof(uint32_t)); p++) {
			out_buffer[p] = (i < 300) ? 0xFFFF0000 : 0xFF0000FF;
		}
		int x = (cos((double) i * 6.28 / 60.0) * 300.0 + 350.0);
		int y = (sin((double) i * 6.28 / 60.0) * 300.0 + 350.0);
		gfx_slow_swizzling_blit(out_buffer, reswitched_logo_pixels, 64, 64, x, y);
		
		ASSERT_OK(fail_display_event, surface_queue_buffer(&surf));

		uint32_t handle_idx;
		r = svcWaitSynchronization(&handle_idx, &vsync, 1, 33333333);
		if(r != RESULT_OK) {
			printf("vsync timed out\n");
			goto fail_display_event;
		}
		ASSERT_OK(fail_display_event, svcResetSignal(vsync));
	}

fail_display_event:
	svcCloseHandle(vsync);
fail_display_layer:
	display_close_layer(&surf);
fail_display:
	display_finalize();
fail_vi:
	vi_finalize();
fail_gpu:
	gpu_finalize();
fail_sm:
	sm_finalize();
fail:
	return r != RESULT_OK;
}
