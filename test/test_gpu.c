#include<libtransistor/nx.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		dbg_printf("assertion failed at %s:%d: result 0x%x is not OK", __FILE__, __LINE__, r); \
		goto label; \
	}

#define ASSERT_EQ(label, a, b, fmt) if((a) != (b)) {	  \
		dbg_printf("assertion failed at %s:%d: %s != %s (" fmt " != " fmt ")", __FILE__, __LINE__, (a), (b)); \
		goto label; \
	}

static uint8_t __attribute__((aligned(0x1000))) buf[0x1000];

int main() {
	svcSleepThread(100000000);

	result_t r;
	ASSERT_OK(fail, sm_init())
		ASSERT_OK(fail_sm, gpu_initialize())

		dbg_printf("initialized gpu");

	gpu_buffer_t gpu_b;
	ASSERT_OK(fail_gpu, gpu_buffer_initialize(&gpu_b, buf, sizeof(buf), 0, 0, 0x1000, 0));

	dbg_printf("created buffer! nvmap handle = %d", gpu_b.nvmap_handle);
  
	uint32_t buffer_id;
	ASSERT_OK(fail_gpu, gpu_buffer_get_id(&gpu_b, &buffer_id));

	dbg_printf("got buffer id: %d", buffer_id);

	gpu_buffer_t gpu_b2;
	ASSERT_OK(fail_gpu, gpu_buffer_initialize_from_id(&gpu_b2, buffer_id));
	dbg_printf("created from id:");
	dbg_printf("  nvmap handle: %d", gpu_b2.nvmap_handle);
	dbg_printf("  size: 0x%x", gpu_b2.size);
	dbg_printf("  alignment: 0x%x", gpu_b2.alignment);
	dbg_printf("  kind: %d", gpu_b2.kind);

	ASSERT_EQ(fail_gpu, gpu_b.size, gpu_b2.size, "0x%x");
	ASSERT_EQ(fail_gpu, gpu_b.alignment, gpu_b2.alignment, "0x%x");
	ASSERT_EQ(fail_gpu, gpu_b.kind, gpu_b2.kind, "%d");

	dbg_printf("gpu test passed");
  
fail_gpu:
	gpu_finalize();
fail_sm:
	sm_finalize();
fail:
	return r != RESULT_OK;
}
