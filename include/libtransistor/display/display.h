/**
 * @file libtransistor/display/display.h
 * @brief Display data structures and functions
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/surface.h>

/**
* @struct display_t
* @brief Represents a physical display
*/
typedef struct {
	uint64_t id;
	revent_h vsync;
} display_t;

/**
* @brief Initialize Display
*/
result_t display_init();

/**
* @brief Open a display layer
*
* @param surface Surface structure to initialize
*/
result_t display_open_layer(surface_t *surface);

/**
* @brief Get a V-Sync event
*
* @param event Output
*/
result_t display_get_vsync_event(revent_h *event);

/**
 * @brief Close a display layer
 *
 * @param surface Surface to close
 */
void display_close_layer(surface_t *surface);

/**
* @brief Finalize Display
*/
void display_finalize();
