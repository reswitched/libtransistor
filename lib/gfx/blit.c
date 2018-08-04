#include<libtransistor/types.h>
#include<libtransistor/gfx/blit.h>

static int pdep(uint32_t mask, uint32_t value) {
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

static uint32_t swizzle_x(uint32_t v) { return pdep(~0x7B4u, v); }
static uint32_t swizzle_y(uint32_t v) { return pdep(0x7B4, v); }

void gfx_slow_swizzling_blit(uint32_t *buffer, uint32_t *image, int w, int h, int tx, int ty) {
  uint32_t *dest = buffer;
  uint32_t *src = image;
  uint32_t x0 = tx;
  uint32_t y0 = ty;
  uint32_t x1 = x0+w;
  uint32_t y1 = y0+h;
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
