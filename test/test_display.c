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

static void swizzle_image(uint32_t *graphics_buffer, uint32_t *image) {
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
	ASSERT_OK(fail_sm, gpu_initialize());
	ASSERT_OK(fail_gpu, vi_init());
	ASSERT_OK(fail_vi, display_init());
	
	printf("initialized all modules\n");

	surface_t surf;
	ASSERT_OK(fail_display, display_open_layer(&surf));
	
	for(int i = 0; i < 600; i++) {
		printf("begin frame %d\n", i);
		uint32_t *out_buffer;
		ASSERT_OK(fail_display, surface_dequeue_buffer(&surf, &out_buffer));

		for(int p = 0; p < (0x3c0000/sizeof(uint32_t)); p++) {
			out_buffer[p] = 0xFF0000FF;
		}
		int x = (cos((double) i * 6.28 / 60.0) * 300.0 + 350.0);
		int y = (sin((double) i * 6.28 / 60.0) * 300.0 + 350.0);
		blit(out_buffer, reswitched_logo_data, 64, 64, x, y);
		
		ASSERT_OK(fail_display, surface_queue_buffer(&surf));
		
		svcSleepThread(16666667);
	}

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
