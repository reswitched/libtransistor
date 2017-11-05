#include<libtransistor/nx.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
    dbg_printf("assertion failed at %s:%d: result 0x%x is not OK", __FILE__, __LINE__, r); \
    goto label;                                                         \
  }

int main() {
  svcSleepThread(100000000);

  result_t r;
  ASSERT_OK(fail, sm_init())
  ASSERT_OK(fail_sm, vi_init())

  dbg_printf("initialized vi");

 fail_vi:
  vi_finalize();
 fail_sm:
  sm_finalize();
 fail:
  return r != RESULT_OK;
}
