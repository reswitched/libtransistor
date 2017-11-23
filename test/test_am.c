#include<libtransistor/nx.h>

#include<string.h>
#include<stdio.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

int main() {
  svcSleepThread(100000000);
  
  result_t r = RESULT_OK;
  printf("init sm\n");
  ASSERT_OK(fail, sm_init());
  printf("init am\n");
  ASSERT_OK(fail_sm, am_init());
  printf("initialized am\n");
  
  am_finalize();
 fail_sm:
  sm_finalize();
 fail:
  return r != RESULT_OK;
}
