#include<libtransistor/nx.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
    dbg_printf("assertion failed at %s:%d: result 0x%x is not OK", __FILE__, __LINE__, r); \
    goto label;                                                         \
  }

void dump_controller_color(char *title, hid_controller_color_t color) {
  dbg_printf("  %s:", title);
  dbg_printf("    body: 0x%x", color.body);
  dbg_printf("    buttons: 0x%x", color.buttons);
}

int main() {
  svcSleepThread(100000000);
  
  result_t r;
  ASSERT_OK(fail, sm_init());
  ASSERT_OK(fail_sm, hid_init());

  hid_controller_t *controllers = hid_get_shared_memory()->controllers;

  dbg_printf("dumping controller states:");
  for(int i = 0; i < 10; i++) {
    hid_controller_t *c = controllers + i;
    dbg_printf("controller #%d:", i);
    dbg_printf("  status: 0x%x", c->status);
    dbg_printf("  is_joycon_half: %d", c->is_joycon_half);
    dbg_printf("  unknown1: 0x%x", c->unknown1);
    dump_controller_color("single color", c->single_color);
    dbg_printf("  unknown2: 0x%x", c->unknown2);
    dump_controller_color("right color", c->right_color);
    dump_controller_color("left color", c->left_color);
  }
  
  hid_finalize();
  sm_finalize();
  return 0;
  
 fail_sm:
  sm_finalize();
 fail:
  return 1;
}
