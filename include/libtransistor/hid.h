#pragma once

#include<libtransistor/types.h>

typedef struct {
	uint8_t data[0x3000];
} hid_touchscreen_t;

typedef struct {
	uint8_t data[0x400];
} hid_mouse_t;

typedef struct {
	uint8_t data[0x400];
} hid_keyboard_t;

typedef struct {
	uint8_t mac[0x10];
} hid_mac;

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

typedef struct {
	uint64_t timestamp;
	uint64_t num_entries;
	uint64_t latest_idx;
	uint64_t max_idx;
	hid_controller_state_entry_t entries[17];
} hid_controller_state_t;

typedef struct {
	uint32_t body;
	uint32_t buttons;
} hid_controller_color_t;

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

typedef struct {
	uint8_t pad1[0x400];
	hid_touchscreen_t touchscreen;
	hid_mouse_t mouse;
	hid_keyboard_t keyboard;
	uint8_t unknown1[0x400];
	uint8_t unknown2[0x400];
	uint8_t unknown3[0x400];
	uint8_t unknown4[0x400];
	uint8_t unknown5[0x200];
	uint8_t unknown6[0x200];
	uint8_t unknown7[0x200];
	uint8_t pad2[0x800];
	uint8_t controller_serials[0x4000];
	hid_controller_t controllers[10];
	uint8_t unknown8[0x4600];
} hid_shared_memory_t;

result_t hid_init();
hid_shared_memory_t *hid_get_shared_memory();
void hid_finalize();
