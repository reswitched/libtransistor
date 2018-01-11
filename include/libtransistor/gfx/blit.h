/**
 * @file libtransistor/gfx/blit.h
 * @brief Functions for graphics blits
 */

#pragma once

/**
* @brief An IPC request with default values set
*
* @param framebuffer Pointer to the framebuffer
* @param image Description here...
* @param w Width
* @param h Height
* @param tx Texture X
* @param ty Texture Y
*/
void gfx_slow_swizzling_blit(uint32_t *framebuffer, uint32_t *image, int w, int h, int tx, int ty);
