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

static uint8_t __attribute__((aligned(0x1000))) gpu_buffer_memory[0x780000];

int pdep(uint32_t mask, uint32_t value) {
	uint32_t out = 0;
	for (int shift = 0; shift < 32; shift++) {
		uint32_t bit = 1u << shift;
		if (mask & bit) {
			if (value & 1)
				out |= bit;
			value >>= 1;
		}
	}
	return out;
}

uint32_t swizzle_x(uint32_t v) { return pdep(~0x7B4u, v); }
uint32_t swizzle_y(uint32_t v) { return pdep(0x7B4, v); }

void blit(uint32_t *buffer, uint32_t *image, int w, int h, int tx, int ty) {
  uint32_t *dest = buffer;
  uint32_t *src = image;
  int x0 = tx;
  int y0 = ty;
  int x1 = x0+w;
  int y1 = y0+h;
  const uint32_t tile_height = 128;
  const uint32_t padded_width = 128 * 10;

  // we're doing this in pixels - should just shift the swizzles instead
  uint32_t offs_x0 = swizzle_x(x0);
  uint32_t offs_y  = swizzle_y(y0);
  uint32_t x_mask  = swizzle_x(~0u);
  uint32_t y_mask  = swizzle_y(~0u);
  uint32_t incr_y  = swizzle_x(padded_width);

  // step offs_x0 to the right row of tiles
  offs_x0 += incr_y * (y0 / tile_height);

  uint32_t x, y;
  for (y=y0; y < y1; y++) {
    uint32_t *dest_line = dest + offs_y;
    uint32_t offs_x = offs_x0;

    for (x=x0; x < x1; x++) {
      uint32_t pixel = *src++;
      dest_line[offs_x] = pixel;
      offs_x = (offs_x - x_mask) & x_mask;
    }

    offs_y = (offs_y - y_mask) & y_mask;
    if (!offs_y) offs_x0 += incr_y; // wrap into next tile row
  }
}

static uint32_t swizzle_image(uint32_t *graphics_buffer, uint32_t *image) {
	uint32_t p = 0;
	uint32_t swizzle = 0x384b;
	for (uint32_t y = 0; y < 720; y++) {
		for (uint32_t x = 0; x < 1280; x++) {
			// actual addressing
			uint32_t tileX = x / 128;
			uint32_t tileY = y / 128;
			uint32_t inTileX = x % 128;
			uint32_t inTileY = y % 128;
			
			uint32_t *tile = &image[(tileY * 10 + tileX) * (128 * 128)];
			
			uint32_t inTileCoord = inTileY * 128 + inTileX;
			//assert(inTileCoord <= 0x3fff);
			
			int mask = swizzle;
			
			int xPart = pdep(mask, inTileX);
			int yPart = pdep(~mask, inTileY);
			//assert((xPart & yPart) == 0);
			inTileCoord = xPart | yPart;
			
			graphics_buffer[p++] = tile[inTileCoord];
		}
	}
}

uint32_t image[1280*720];

int main() {
	svcSleepThread(100000000);
  
	result_t r;
	ASSERT_OK(fail, sm_init());
	ASSERT_OK(fail_sm, am_init());
	ASSERT_OK(fail_sm, gpu_initialize());
	ASSERT_OK(fail_gpu, vi_init());
	
	printf("init'd gpu and vi\n");
	
	display_t display;
	ASSERT_OK(fail_vi, vi_open_display("Default", &display));
	printf("opened display\n");
	
	//ASSERT_OK(fail_vi, vi_iads_set_display_enabled(true, &display));
  
	surface_t surf;

	aruid_t aruid;
	ASSERT_OK(fail_vi, am_iwc_get_applet_resource_user_id(&aruid));
	printf("got aruid: %d\n", aruid);

	ASSERT_OK(fail_vi, am_isc_approve_to_display());
	printf("approved to display\n");
	
	ASSERT_OK(fail_vi, am_iwc_acquire_foreground_rights());
	printf("got foreground rights\n");

	uint64_t layer_id;
	ASSERT_OK(fail_vi, am_isc_create_managed_display_layer(&layer_id));
	dbg_printf("managed layer id from am: %ld", layer_id);
	
	//uint64_t my_layer_id;
	//ASSERT_OK(fail_vi, vi_create_managed_layer(1, &display, 0, &my_layer_id));
	//dbg_printf("managed layer id: %d", my_layer_id);
	
	ASSERT_OK(fail_vi, vi_open_layer("Default", layer_id, aruid, &surf));
	dbg_printf("opened managed layer");

	printf("adjusting refcount\n");
	ASSERT_OK(fail_vi, binder_adjust_refcount(&surf.igbp_binder, 1, 0));
	ASSERT_OK(fail_vi, binder_adjust_refcount(&surf.igbp_binder, 1, 1));
	printf("adjusted refcount\n");

	// get native handle?
  
	int status;
	queue_buffer_output_t qbo;
	ASSERT_OK(fail_vi, surface_connect(&surf, 2, false, &status, &qbo));
	
	printf("IGBP_CONNECT:\n");
	printf("  status: %d\n", status);
	printf("  qbo:\n");
	printf("    width: %d\n", qbo.width);
	printf("    height: %d\n", qbo.height);
	printf("    transform_hint: %d\n", qbo.transform_hint);
	printf("    num_pending_buffers: %d\n", qbo.num_pending_buffers);
	
	if(status != 0) {
		printf("IGBP_CONNECT failure\n");
		goto fail_vi;
	}

	ASSERT_OK(fail_vi, vi_iads_set_layer_scaling_mode(2, &surf));

	// get vsync event?

	// QUERY?
	
	ASSERT_OK(fail_vi, svcSetMemoryAttribute(gpu_buffer_memory, sizeof(gpu_buffer_memory), 0x8, 0x8));
  
	gpu_buffer_t gpu_buffer;
	ASSERT_OK(fail_vi, gpu_buffer_initialize(&gpu_buffer, gpu_buffer_memory, sizeof(gpu_buffer_memory), 0, 0, 0x1000, 0));
  
	graphic_buffer_t graphic_buffer_0;
	graphic_buffer_0.width = 1280;
	graphic_buffer_0.height = 720;
	graphic_buffer_0.stride = 1280;
	graphic_buffer_0.format = 1;
	graphic_buffer_0.usage = 0xb00;
	graphic_buffer_0.gpu_buffer = &gpu_buffer;
  
	graphic_buffer_t graphic_buffer_1 = graphic_buffer_0;
	graphic_buffer_0.unknown = 0;
	graphic_buffer_1.unknown = 0x3c0000;
  
	ASSERT_OK(fail_vi, surface_set_preallocated_buffer(&surf, 0, &graphic_buffer_0));
	ASSERT_OK(fail_vi, surface_set_preallocated_buffer(&surf, 1, &graphic_buffer_1));

	bool requested[2] = {0, 0};

	printf("adding to layer stacks...\n");
	ASSERT_OK(fail_vi, vi_imds_add_to_layer_stack(0x5, &surf));
	ASSERT_OK(fail_vi, vi_imds_add_to_layer_stack(0x4, &surf));
	ASSERT_OK(fail_vi, vi_imds_add_to_layer_stack(0x2, &surf));
	ASSERT_OK(fail_vi, vi_imds_add_to_layer_stack(0xA, &surf));
	ASSERT_OK(fail_vi, vi_imds_add_to_layer_stack(0x0, &surf));
	ASSERT_OK(fail_vi, vi_isds_set_layer_z(&surf, 2));
	
	for(int i = 0; i < 600; i++) {
		int slot;
		fence_t fence;
		ASSERT_OK(fail_vi, surface_dequeue_buffer(&surf, 1280, 720, 1, 0xb00, false, &status, &slot, &fence, NULL));
		if(status != 0) {
			printf("IGBP_DEQUEUE_BUFFER failure: %d\n", status);
			goto fail_vi;
		}    
    
		if(!requested[slot]) {
			graphic_buffer_t graphic_buffer_rq;
			ASSERT_OK(fail_vi, surface_request_buffer(&surf, slot, &status, &graphic_buffer_rq));
			if(status != 0) {
				printf("IGBP_REQUEST_BUFFER failure: %d\n", status);
				goto fail_vi;
			}
			printf("IGBP_REQUEST_BUFFER:\n");
			printf("  status: %d\n", status);

			memory_info_t meminfo;
			uint32_t pageinfo;
			ASSERT_OK(fail_vi, svcQueryMemory(&meminfo, &pageinfo, gpu_buffer_memory));
			printf("gpu buffer dev refcount: %d\n", meminfo.device_ref_count);
			printf("gpu buffer size: 0x%lx (should be 0x%lx)\n", meminfo.size, sizeof(gpu_buffer_memory));
      
			requested[slot] = true;
		}

		uint32_t *out_buffer = gpu_buffer_memory + (slot * 0x3c0000);
		/*memset(image, 0x22, 1280*720);
		for(int x = 0; x < 1280; x++) {
			image[x] = 0xFF00FF00;
		}
		for(int y = 0; y < 720; y++) {
			image[y*1280] = 0xFF0000FF;
		}
		for(int d = 0; d < 720; d++) {
			image[(d*1280)+d] = 0xFFFF0000;
		}
		swizzle_image(out_buffer, image);*/
		memset(out_buffer, 0x22, 0x3c0000);
		int x = (cos((double) i * 6.28 / 60.0) * 300.0 + 350.0);
		int y = (sin((double) i * 6.28 / 60.0) * 300.0 + 350.0);
		blit(out_buffer, reswitched_logo_data, 64, 64, x, y);
		
		ASSERT_OK(fail_vi, surface_queue_buffer(&surf, slot, NULL, &qbo, &status));
		if(status != 0) {
			printf("IGBP_QUEUE_BUFFER failure: %d\n", status);
			goto fail_vi;
		}

		svcSleepThread(16666667);
	}
  
fail_vi:
	vi_finalize();
fail_gpu:
	gpu_finalize();
fail_am:
	am_finalize();
fail_sm:
	sm_finalize();
fail:
	return r != RESULT_OK;
}
