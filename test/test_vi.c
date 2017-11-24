#include<libtransistor/nx.h>

#include<stdio.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

int main() {
	svcSleepThread(100000000);

	result_t r;
	ASSERT_OK(fail, sm_init());
	ASSERT_OK(fail_sm, vi_init());

	printf("initialized vi\n");

	display_t display;
	ASSERT_OK(fail_vi, vi_open_display("Default", &display));

	surface_t surf;
	ASSERT_OK(fail_vi, vi_create_stray_layer(1, &display, &surf));

	printf("created stray layer\n");
	printf("  layer id: 0x%lx\n", surf.layer_id);
	printf("  binder handle: 0x%x\n", surf.igbp_binder.handle);

	int status;
	queue_buffer_output_t qbo;
  
	ASSERT_OK(fail_vi, surface_connect(&surf, 2, false, &status, &qbo));

	printf("IGBP_CONNECT:\n");
	printf("  status: %d\n", status);
	printf("  qbo:\n");
	printf("    width: %d\n", qbo.width);
	printf("    height: %d\n", qbo.height);
	printf("    transform_hint: %d\n", qbo.transform_hint);
	printf("    num_pending_buffers: %d\n", qbo.num_pending_buffers);
  
fail_vi:
	vi_finalize();
fail_sm:
	sm_finalize();
fail:
	return r != RESULT_OK;
}
