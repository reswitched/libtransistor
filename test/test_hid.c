#include<libtransistor/nx.h>

#include<stdio.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

void dump_controller_color(char *title, hid_controller_color_t color) {
	printf("  %s:\n", title);
	printf("    body: 0x%x\n", color.body);
	printf("    buttons: 0x%x\n", color.buttons);
}

int main() {
	svcSleepThread(100000000);
  
	result_t r;
	ASSERT_OK(fail, sm_init());
	ASSERT_OK(fail_sm, hid_init());

	hid_controller_t *controllers = hid_get_shared_memory()->controllers;

	printf("dumping controller states:\n");
	for(int i = 0; i < 10; i++) {
		hid_controller_t *c = controllers + i;
		printf("controller #%d:\n", i);
		printf("  status: 0x%x\n", c->status);
		printf("  is_joycon_half: %d\n", c->is_joycon_half);
		printf("  unknown1: 0x%x\n", c->unknown1);
		dump_controller_color("single color", c->single_color);
		printf("  unknown2: 0x%x\n", c->unknown2);
		dump_controller_color("right color", c->right_color);
		dump_controller_color("left color", c->left_color);
	}

	for(int i = 0; i < 200; i++) {
		hid_controller_t *num8 = controllers + 8;
		hid_controller_state_entry_t ent = num8->main.entries[num8->main.latest_idx];
		printf("num8: 0x%16lx, (%d, %d), (%d, %d)\n", ent.button_state, ent.left_stick_x, ent.left_stick_y, ent.right_stick_x, ent.right_stick_y);

		hid_touchscreen_t touchscreen = hid_get_shared_memory()->touchscreen;
		hid_touch_entry_t latest = touchscreen.touch_entry[touchscreen.latest_idx];
		printf("Touch count: %u %u\n", latest.num_touches, touchscreen.latest_idx);
		for (int j = 0; j < latest.num_touches; j++) {
			printf("Touch %u:\t(%u, %u)\n", j, latest.touch_data[j].touch_x, latest.touch_data[j].touch_y);
		}

		svcSleepThread(50000000);
	}
	
	hid_finalize();
	sm_finalize();
	return 0;
  
fail_sm:
	sm_finalize();
fail:
	return 1;
}
