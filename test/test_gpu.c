#include<libtransistor/nx.h>

#include<stdio.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

#define ASSERT_EQ(label, a, b, fmt) if((a) != (b)) {	  \
		printf("assertion failed at %s:%d: " #a " != " #b " (" fmt " != " fmt ")\n", __FILE__, __LINE__, (a), (b)); \
		goto label; \
	}

static uint8_t __attribute__((aligned(0x1000))) buf[0x1000];

int main() {
	svcSleepThread(100000000);

	result_t r;
	ASSERT_OK(fail, sm_init());
	ASSERT_OK(fail_sm, gpu_initialize());
	
	printf("initialized gpu\n");
	
	gpu_buffer_t gpu_b;
	ASSERT_OK(fail_gpu, gpu_buffer_initialize(&gpu_b, buf, sizeof(buf), 0, 0, 0x1000, 0));

	printf("created buffer! nvmap handle = %d\n", gpu_b.nvmap_handle);
  
	uint32_t buffer_id;
	ASSERT_OK(fail_gpu, gpu_buffer_get_id(&gpu_b, &buffer_id));

	printf("got buffer id: %d\n", buffer_id);

	gpu_buffer_t gpu_b2;
	ASSERT_OK(fail_gpu, gpu_buffer_initialize_from_id(&gpu_b2, buffer_id));
	printf("created from id:\n");
	printf("  nvmap handle: %d\n", gpu_b2.nvmap_handle);
	printf("  size: 0x%zx\n", gpu_b2.size);
	printf("  alignment: 0x%x\n", gpu_b2.alignment);
	printf("  kind: %d\n", gpu_b2.kind);

	ASSERT_EQ(fail_gpu, gpu_b.size, gpu_b2.size, "0x%zx");
	ASSERT_EQ(fail_gpu, gpu_b.alignment, gpu_b2.alignment, "0x%x");
	ASSERT_EQ(fail_gpu, gpu_b.kind, gpu_b2.kind, "%d");

	printf("gpu test passed\n");
  
fail_gpu:
	gpu_finalize();
fail_sm:
	sm_finalize();
fail:
	return r != RESULT_OK;
}
