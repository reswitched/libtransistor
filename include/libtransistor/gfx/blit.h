/**
 * @file libtransistor/gfx/blit.h
 * @brief Functions for graphics blits
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Copies pixels from image to framebuffer, swizzling them into the format the GPU expects.
*
* @param framebuffer Pointer to the framebuffer, usually acquired from \ref surface_dequeue_buffer
* @param image Image to copy pixels from
* @param w Width of \ref image
* @param h Height of \ref image
* @param tx Target X
* @param ty Target Y
*/
void gfx_slow_swizzling_blit(uint32_t *framebuffer, uint32_t *image, int w, int h, int tx, int ty);

#ifdef __cplusplus
}
#endif
