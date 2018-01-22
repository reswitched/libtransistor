/**
 * @file libtransistor/display/rect.h
 * @brief Rectangle
 */

#pragma once

#include<libtransistor/types.h>

/**
* @struct rect_t
* @brief A simple rectangle
*/
typedef struct {
	uint32_t left;
	uint32_t top;
	uint32_t right;
	uint32_t bottom;
} rect_t;
