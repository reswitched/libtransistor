#include<libtransistor/nx.h>

#include<string.h>
#include<stdlib.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		dbg_printf("assertion failed at %s:%d: result 0x%x is not OK", __FILE__, __LINE__, r); \
		goto label; \
	}

static uint8_t __attribute__((aligned(0x1000))) gpu_buffer_memory[0x780000];
static int bsdlog;
static result_t setup_log();

int main() {
	svcSleepThread(100000000);
  
	result_t r;
	ASSERT_OK(fail, sm_init());
	ASSERT_OK(fail_sm, bsd_init());

	if((r = setup_log()) != RESULT_OK) {
		goto fail_bsd;
	}
  
	ASSERT_OK(fail_bsdlog, gpu_initialize());
	ASSERT_OK(fail_gpu, vi_init());

	dbg_printf("init'd gpu and vi");
  
	display_t display;
	ASSERT_OK(fail_vi, vi_open_display("Default", &display));

	//ASSERT_OK(fail_vi, vi_iads_set_display_enabled(true, &display));
  
	surface_t surf;
	ASSERT_OK(fail_vi, vi_create_stray_layer(1, &display, &surf));
	/*uint64_t my_layer_id;
	  ASSERT_OK(fail_vi, vi_create_managed_layer(1, &display, 0, &my_layer_id));
	  dbg_printf("managed layer id: %d", my_layer_id);
	  ASSERT_OK(fail_vi, vi_open_layer("Default", my_layer_id, 0, &surf));
	  dbg_printf("opened managed layer");*/

	int64_t z;
  
	ASSERT_OK(fail_vi, vi_iads_set_layer_scaling_mode(2, &surf));
  
	/*ASSERT_OK(fail_vi, vi_imds_set_layer_visibility(true, &surf));
	  ASSERT_OK(fail_vi, vi_isds_set_layer_visibility(true, &surf));
	  //ASSERT_OK(fail_vi, vi_isds_set_layer_size(&surf, 1280, 720));
  
	  dbg_printf("trying to add to layer stack(s)...");
	  for(int i = 0; i < 11; i++) {
	  dbg_printf("  stack %d: 0x%x", i, vi_imds_add_to_layer_stack(i, &surf));
	  }
	  //ASSERT_OK(fail_vi, vi_imds_set_display_layer_stack(0, &display));
	  ASSERT_OK(fail_vi, vi_imds_set_conductor_layer(true, &surf));
	  ASSERT_OK(fail_vi, vi_imds_set_content_visibility(true));*/
    
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

	ASSERT_OK(fail_vi, svcSetMemoryAttribute(gpu_buffer_memory, sizeof(gpu_buffer_memory), 0x8, 0x8));
  
	gpu_buffer_t gpu_buffer;
	ASSERT_OK(fail_vi, gpu_buffer_initialize(&gpu_buffer, gpu_buffer_memory, sizeof(gpu_buffer_memory), 0, 0, 0x1000, 0));
  
	memset(gpu_buffer_memory, 0x66, sizeof(gpu_buffer_memory));
  
	graphic_buffer_t graphic_buffer_0;
	graphic_buffer_0.width = 1280;
	graphic_buffer_0.height = 720;
	graphic_buffer_0.stride = 1280;
	graphic_buffer_0.format = 1;
	graphic_buffer_0.usage = 0xb33;
	graphic_buffer_0.gpu_buffer = &gpu_buffer;
  
	graphic_buffer_t graphic_buffer_1 = graphic_buffer_0;
	graphic_buffer_0.unknown = 0;
	graphic_buffer_1.unknown = 0x3c;
  
	ASSERT_OK(fail_vi, surface_set_preallocated_buffer(&surf, 0, &graphic_buffer_0));
	ASSERT_OK(fail_vi, surface_set_preallocated_buffer(&surf, 1, &graphic_buffer_1));

	bool requested[2] = {0, 0};

	queue_buffer_input_t qbi;
	memset(&qbi, 0, sizeof(qbi));

	qbi.timestamp = 0x54;
	qbi.is_auto_timestamp = true;
	qbi.crop.left = 0;
	qbi.crop.top = 0;
	qbi.crop.right = 1280;
	qbi.crop.bottom = 720;
	qbi.scaling_mode = 2;
	qbi.transform = 1;

	/*
	  layers:
	  6 - overlay notification stuff
	*/

	dbg_printf("set z result : 0x%x", vi_isds_set_layer_z(&surf, 4));
	ASSERT_OK(fail_vi, vi_isds_get_layer_z(&surf, &z));
	dbg_printf("z: %d", z);
  
	//int64_t zc_min, zc_max;
	//ASSERT_OK(fail_vi, vi_isds_get_z_order_count_min(&surf, &zc_min));
	//ASSERT_OK(fail_vi, vi_isds_get_z_order_count_max(&surf, &zc_max));
	//dbg_printf("z order min, max: %ld, %ld", zc_min, zc_max);
  
	dbg_printf("probing layers...");
	for(int i = 0; i < surf.layer_id; i++) {
		surface_t fake;
		fake.layer_id = i;
		r = vi_isds_get_layer_z(&fake, &z);
		if(r) {
			dbg_printf("%d: error 0x%x", i, r);
		} else {
			dbg_printf("%d: z %d", i, z);
			/*if(i != 6) {
			  ASSERT_OK(fail_vi, vi_isds_set_layer_visibility(false, &fake));
			  ASSERT_OK(fail_vi, vi_imds_set_layer_visibility(false, &fake));
			  dbg_printf("  => disabled");
			  } else {
			  ASSERT_OK(fail_vi, vi_isds_set_layer_visibility(true, &fake));
			  ASSERT_OK(fail_vi, vi_imds_set_layer_visibility(true, &fake));
			  dbg_printf("  => enabled");
			  }*/
			dbg_printf("  pos: 0x%x", vi_isds_set_layer_position(0.0f, 0.0f, &fake));
		}
	}

	for(size_t i = 0; i < sizeof(gpu_buffer_memory); i+= sizeof(int)) {
		*((int*) (gpu_buffer_memory + i)) = rand();
	}
  
	for(int i = 0; i < 6; i++) {
		svcSleepThread(5000000);
		int slot;
		fence_t fence;
		ASSERT_OK(fail_vi, surface_dequeue_buffer(&surf, 1280, 720, 1, 0x300, false, &status, &slot, &fence, NULL));
		if(status != 0) {
			dbg_printf("IGBP_DEQUEUE_BUFFER failure: %d", status);
			goto fail_vi;
		}
    
		dbg_printf("IGBP_DEQUEUE_BUFFER:");
		dbg_printf("  status: %d", status);
		dbg_printf("  slot: %d", slot);
		dbg_printf("  fence:");
		hexdump(&fence, sizeof(fence));
		dbg_printf("(hexdump end)");
    
		if(!requested[slot]) {
			graphic_buffer_t graphic_buffer_rq;
			ASSERT_OK(fail_vi, surface_request_buffer(&surf, slot, &status, &graphic_buffer_rq));
			if(status != 0) {
				dbg_printf("IGBP_REQUEST_BUFFER failure: %d", status);
				goto fail_vi;
			}
			dbg_printf("IGBP_REQUEST_BUFFER:");
			dbg_printf("  status: %d", status);

			memory_info_t meminfo;
			uint32_t pageinfo;
			ASSERT_OK(fail_vi, svcQueryMemory(&meminfo, &pageinfo, gpu_buffer_memory));
			dbg_printf("gpu buffer dev refcount: %d", meminfo.device_ref_count);
			dbg_printf("gpu buffer size: 0x%lx (should be 0x%lx)", meminfo.size, sizeof(gpu_buffer_memory));
      
			requested[slot] = true;
		}

		//memset(gpu_buffer_memory, 0xff, sizeof(gpu_buffer_memory));
		dbg_printf("gpubm+0x1000");
		hexdump(gpu_buffer_memory + 0x1000, 0x20);
    
		fence_t tfence = {{0x1, 0x25, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
		qbi.fence = tfence;

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

		dbg_printf("done with frame %d", i);
    
		dbg_printf("i sleep");
		svcSleepThread(1000000000);
		dbg_printf("woke");
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

result_t setup_log() {
	result_t r = RESULT_OK;
  
	struct addrinfo_fixed aif;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if(bsd_getaddrinfo_fixed("conntest.nintendowifi.net", "7878", &hints, &aif, 1) != 0) {
		dbg_printf("failed to resolve conntest.nintendowifi.net");
		r = bsd_result;
		goto fail_bsd;
	}
  
	bsdlog = bsd_socket(aif.ai.ai_family, aif.ai.ai_socktype, aif.ai.ai_protocol);
	if(bsdlog < 0) {
		dbg_printf("failed to create socket: 0x%x, %d", bsd_result, bsd_errno);
		r = bsd_result;
		goto fail_bsd;
	}
	if(bsd_connect(bsdlog, (struct sockaddr*) aif.ai.ai_addr, aif.ai.ai_addrlen) != 0) {
		dbg_printf("failed to connect log: 0x%x, %d", bsd_result, bsd_errno);
		r = bsd_result;
		goto fail_bsdlog;
	}
	dbg_set_bsd_log(bsdlog);
	dbg_printf("connected log.");
	return RESULT_OK;
  
fail_bsdlog:
	bsd_close(bsdlog);
fail_bsd:
	return r;
}
