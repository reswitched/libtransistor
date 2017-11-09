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
  ASSERT_OK(fail_sm, bsd_init());

  char log_ip_addr[4] = {10, 0, 0, 192};
  struct sockaddr_in log_addr = {
    .sin_family = AF_INET,
    .sin_port = htons(7878),
    .sin_addr = {
      .s_addr = *(uint32_t*) log_ip_addr
    }
  };

  int bsdlog = bsd_socket(2, 1, 6);
  if(bsdlog < 0) {
    dbg_printf("failed to create socket: 0x%x, %d", bsd_result, bsd_errno);
    goto fail_bsd;
  }
  if(bsd_connect(bsdlog, (struct sockaddr*) &log_addr, sizeof(log_addr)) != 0) {
    dbg_printf("failed to connect log: 0x%x, %d", bsd_result, bsd_errno);
    goto fail_bsdlog;
  }
  dbg_set_bsd_log(bsdlog);

  dbg_printf("connected log.");
  
  ASSERT_OK(fail_bsdlog, gpu_initialize());
  ASSERT_OK(fail_gpu, vi_init());

  dbg_printf("init'd gpu and vi");
  
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

  memset(gpu_buffer_memory, 0x66, sizeof(gpu_buffer_memory));
  
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

  bool requested[2] = {0, 0};

  queue_buffer_input_t qbi;
  memset(&qbi, 0, sizeof(qbi));

  qbi.timestamp = 0x20;
  qbi.is_auto_timestamp = true;
  qbi.crop.left = 0;
  qbi.crop.top = 0;
  qbi.crop.right = 1280;
  qbi.crop.bottom = 720;
  qbi.scaling_mode = 1;
  qbi.transform = 1;

  for(int i = 0; i < 10; i++) {
    svcSleepThread(5000000);
    int slot;
    fence_t fence;
    ASSERT_OK(fail_vi, surface_dequeue_buffer(&surf, 1280, 720, 1, 0x300, false, &status, &slot, &fence, NULL));
    if(status != 0) {
      dbg_printf("IGBP_DEQUEUE_BUFFER failure: %d", status);
      goto fail_vi;
    }
    
    dbg_printf("dequeued buffer in slot %d", slot);

    if(!requested[slot]) {
      graphic_buffer_t graphic_buffer_rq;
      ASSERT_OK(fail_vi, surface_request_buffer(&surf, slot, &status, &graphic_buffer_rq));
      if(status != 0) {
        dbg_printf("IGBP_REQUEST_BUFFER failure: %d", status);
        goto fail_vi;
      }
      dbg_printf("got buffer");
      requested[slot] = true;
    }

    memset(gpu_buffer_memory, 0x66, sizeof(gpu_buffer_memory));

    if(i == 0) {
      fence_t tfence = {{0x24, 0x0, 0x1, 0x0102, 0x13f4, 0xffffffff, 0x0, 0xffffffff, 0x0, 0xffffffff, 0x0}};
      qbi.fence = tfence;
    } else {
      qbi.fence = fence;
    }
    ASSERT_OK(fail_vi, surface_queue_buffer(&surf, slot, &qbi, &qbo, &status));
    dbg_printf("IGBP_QUEUE_BUFFER:");
    dbg_printf("  status: %d", status);
    dbg_printf("  qbo:");
    dbg_printf("    width: %d", qbo.width);
    dbg_printf("    height: %d", qbo.height);
    dbg_printf("    transform_hint: %d", qbo.transform_hint);
    dbg_printf("    num_pending_buffers: %d", qbo.num_pending_buffers);
    if(status != 0) {
      dbg_printf("IGBP_QUEUE_BUFFER failure: %d", status);
      goto fail_vi;
    }
    qbi.timestamp+= 0x100;
  }
  
 fail_vi:
  vi_finalize();
 fail_gpu:
  gpu_finalize();
 fail_bsdlog:
  bsd_close(bsdlog);
 fail_bsd:
  bsd_finalize();
 fail_sm:
  sm_finalize();
 fail:
  return r != RESULT_OK;
}
