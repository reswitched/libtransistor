/**
 * @file libtransistor/hid.h
 * @brief Controller input data structures and functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

/**
 * @struct hid_touch_data_entry_t
 */
typedef struct {
	uint64_t timestamp;
	uint32_t pad1;
	uint32_t touch_idx;
	uint32_t touch_x; /**< 0 is far left of screen, 1280 is far right. */
	uint32_t touch_y; /**< 0 is top of screen, 720 is bottom. */
	uint32_t touch_diameter_x;
	uint32_t touch_diameter_y;
	uint32_t touch_angle;
	uint32_t pad2;
} hid_touch_data_entry_t;

/**
 * @struct hid_touch_data_entry_t
 */
typedef struct {
	uint64_t timestamp;
	uint64_t num_touches;
	hid_touch_data_entry_t touch_data[16];
	uint64_t pad1;
} hid_touch_entry_t;

/**
 * @struct hid_touchscreen_t
 */
typedef struct {
	uint64_t unknown1;
	uint64_t num_entries;
	uint64_t latest_idx;
	uint64_t max_idx;
	uint64_t timestamp;
	hid_touch_entry_t touch_entry[17];
} hid_touchscreen_t;

/**
 * @struct hid_mouse_t
 *
 * Currently a placeholder
 */
typedef struct {
	uint8_t data[0x400];
} hid_mouse_t;

/**
 * @struct hid_keyboard_t
 *
 * Currently a placeholder
 */
typedef struct {
	uint8_t data[0x400];
} hid_keyboard_t;

/**
 * @struct hid_mac
 *
 * MAC address of a controller
 */
typedef struct {
	uint8_t mac[0x10];
} hid_mac;

/**
* @enum hid_controller_button_mask
* @brief Bitmasks for hid_controller_state_entry_t.button_state
*/
typedef enum {
	BUTTON_A		= BIT(0),
	BUTTON_B		= BIT(1),
	BUTTON_X		= BIT(2),
	BUTTON_Y		= BIT(3),

	BUTTON_LSTICK		= BIT(4), // Left stick pressed
	BUTTON_RSTICK		= BIT(5), // Right stick pressed

	BUTTON_L		= BIT(6),
	BUTTON_R		= BIT(7),
	BUTTON_ZL		= BIT(8),
	BUTTON_ZR		= BIT(9),

	BUTTON_PLUS		= BIT(10),
	BUTTON_MINUS		= BIT(11),

	BUTTON_LEFT		= BIT(12),
	BUTTON_UP		= BIT(13),
	BUTTON_RIGHT		= BIT(14),
	BUTTON_DOWN		= BIT(15),

	BUTTON_LSTICK_LEFT	= BIT(16),
	BUTTON_LSTICK_UP	= BIT(17),
	BUTTON_LSTICK_DOWN	= BIT(18),
	BUTTON_LSTICK_RIGHT	= BIT(19),

	BUTTON_RSTICK_LEFT	= BIT(20),
	BUTTON_RSTICK_UP	= BIT(21),
	BUTTON_RSTICK_DOWN	= BIT(22),
	BUTTON_RSTICK_RIGHT	= BIT(23),

	BUTTON_SL		= BIT(24),
	BUTTON_SR		= BIT(25),
} hid_controller_button_mask;

/**
 * @struct hid_controller_state_entry_t
 */
typedef struct {
	uint64_t timestamp;
	uint64_t timestamp2;
	uint64_t button_state;
	uint32_t left_stick_x;
	uint32_t left_stick_y;
	uint32_t right_stick_x;
	uint32_t right_stick_y;
	uint64_t controller_state;
} hid_controller_state_entry_t;

/**
 * @struct hid_controller_state_t
 */
typedef struct {
	uint64_t timestamp;
	uint64_t num_entries;
	uint64_t latest_idx;
	uint64_t max_idx;
	hid_controller_state_entry_t entries[17];
} hid_controller_state_t;

/**
 * @struct hid_controller_color_t
 */
typedef struct {
	uint32_t body;
	uint32_t buttons;
} hid_controller_color_t;

/**
 * @struct hid_controller_t
 */
typedef struct {
	uint32_t status;
	uint32_t is_joycon_half;
	uint32_t unknown1;
	hid_controller_color_t single_color;
	uint32_t unknown2;
	hid_controller_color_t right_color;
	hid_controller_color_t left_color;
  
	hid_controller_state_t pro_controller;
	hid_controller_state_t handheld_joined;
	hid_controller_state_t joined;
	hid_controller_state_t left;
	hid_controller_state_t right;
	hid_controller_state_t main_no_analog;
	hid_controller_state_t main;

	uint8_t pad1[0x2a78];
  
	hid_mac mac[2];

	uint8_t pad2[0xe10];
} hid_controller_t;

/**
 * @struct hid_shared_memory_t
 */
typedef struct {
	uint8_t pad1[0x400];
	hid_touchscreen_t touchscreen;
	uint8_t pad2[0x3c0];
	hid_mouse_t mouse;
	hid_keyboard_t keyboard;
	uint8_t unknown1[0x400];
	uint8_t unknown2[0x400];
	uint8_t unknown3[0x400];
	uint8_t unknown4[0x400];
	uint8_t unknown5[0x200];
	uint8_t unknown6[0x200];
	uint8_t unknown7[0x200];
	uint8_t pad3[0x800];
	uint8_t controller_serials[0x4000];
	hid_controller_t controllers[10];
	uint8_t unknown8[0x4600];
} hid_shared_memory_t;

/**
 * @brief Initialize input
 */
result_t hid_init();

/**
 * @brief Get HID shared memory
 */
hid_shared_memory_t *hid_get_shared_memory();

/**
 * @brief Detect if button(s) are pressed
 */
bool hid_controller_buttons_pressed(hid_controller_t *c, hid_controller_button_mask m);

/**
 * @brief Detect if button(s) are released
 */
bool hid_controller_buttons_released(hid_controller_t *c, hid_controller_button_mask m);

/**
 * @brief Finalize HID
 */
void hid_finalize();

#ifdef __cplusplus
}
#endif
