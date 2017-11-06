#include<libtransistor/nx.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
    dbg_printf("assertion failed at %s:%d: result 0x%x is not OK", __FILE__, __LINE__, r); \
    goto label;                                                         \
  }

static uint8_t __attribute__((aligned(0x1000))) gpu_buffer_memory[0x780000];

int main() {
  svcSleepThread(100000000);
  
  result_t r;
  ASSERT_OK(fail, sm_init());
  ASSERT_OK(fail_sm, gpu_initialize());
  ASSERT_OK(fail_gpu, vi_init());
  
  display_t display;
  ASSERT_OK(fail_vi, vi_open_display("Default", &display));

  surface_t surf;
  ASSERT_OK(fail_vi, vi_create_stray_layer(1, &display, &surf));

  int status;
  queue_buffer_output_t qbo;
  ASSERT_OK(fail_vi, surface_connect(&surf, 2, false, &status, &qbo));

  dbg_printf("IGBP_CONNECT:");
  dbg_printf("  status: %d", status);
  dbg_printf("  qbo:");
  dbg_printf("    width: %d", qbo.width);
  dbg_printf("    height: %d", qbo.height);
  dbg_printf("    transform_hint: %d", qbo.transform_hint);
  dbg_printf("    num_pending_buffers: %d", qbo.num_pending_buffers);

  if(status != 0) {
    dbg_printf("IGBP_CONNECT failure");
    goto fail_vi;
  }
  
  gpu_buffer_t gpu_buffer;
  ASSERT_OK(fail_vi, gpu_buffer_initialize(&gpu_buffer, gpu_buffer_memory, sizeof(gpu_buffer_memory), 0, 0, 0x1000, 0));

  graphic_buffer_t graphic_buffer_0;
  graphic_buffer_0.width = 1280;
  graphic_buffer_0.height = 720;
  graphic_buffer_0.stride = 1280;
  graphic_buffer_0.format = 1;
  graphic_buffer_0.usage = 0xb00;
  graphic_buffer_0.gpu_buffer = &gpu_buffer;
  
  graphic_buffer_t graphic_buffer_1 = graphic_buffer_0;
  graphic_buffer_0.unknown = 0;
  graphic_buffer_1.unknown = 0x3c;
  
  ASSERT_OK(fail_vi, surface_set_preallocated_buffer(&surf, 0, &graphic_buffer_0));
  ASSERT_OK(fail_vi, surface_set_preallocated_buffer(&surf, 1, &graphic_buffer_1));

  int slot;
  fence_t fence;
  ASSERT_OK(fail_vi, surface_dequeue_buffer(&surf, 1280, 720, 1, 0x300, false, &status, &slot, &fence, NULL));
  if(status != 0) {
    dbg_printf("IGBP_DEQUEUE_BUFFER failure: %d", status);
    goto fail_vi;
  }

  dbg_printf("dequeued buffer in slot %d", slot);

  graphic_buffer_t graphic_buffer_rq;
  ASSERT_OK(fail_vi, surface_request_buffer(&surf, slot, &status, &graphic_buffer_rq));
  if(status != 0) {
    dbg_printf("IGBP_REQUEST_BUFFER failure: %d", status);
  }

  dbg_printf("got buffer");
  
 fail_vi:
  vi_finalize();
 fail_gpu:
  gpu_finalize();
 fail_sm:
  sm_finalize();
 fail:
  return r != RESULT_OK;
}
