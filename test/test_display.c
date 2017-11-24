#include<libtransistor/nx.h>

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

static uint8_t __attribute__((aligned(0x1000))) gpu_buffer_memory[0x780000];

int main() {
	svcSleepThread(100000000);
  
	result_t r;
	ASSERT_OK(fail, sm_init());
	ASSERT_OK(fail_sm, am_init());
	ASSERT_OK(fail_am, gpu_initialize());
	ASSERT_OK(fail_gpu, vi_init());
	
	printf("init'd gpu and vi\n");
  
	display_t display;
	ASSERT_OK(fail_vi, vi_open_display("Default", &display));

	//ASSERT_OK(fail_vi, vi_iads_set_display_enabled(true, &display));
  
	surface_t surf;

	uint64_t layer_id;
	ASSERT_OK(fail_vi, am_isc_create_managed_display_layer(&layer_id));
	printf("got managed display layer from am: %ld\n", layer_id);

	aruid_t aruid;
	ASSERT_OK(fail_vi, am_iwc_get_applet_resource_user_id(&aruid));
	printf("got aruid: %ld\n", aruid);

	ASSERT_OK(fail_vi, am_isc_approve_to_display());
	printf("approved to display\n");
	
	ASSERT_OK(fail_vi, am_iwc_acquire_foreground_rights());
	printf("got foreground rights\n");
	
	//ASSERT_OK(fail_vi, vi_create_stray_layer(1, &display, &surf));
	
	/*uint64_t my_layer_id;
	  ASSERT_OK(fail_vi, vi_create_managed_layer(1, &display, 0, &my_layer_id));
	  dbg_printf("managed layer id: %d", my_layer_id);*/
	
	ASSERT_OK(fail_vi, vi_open_layer("Default", layer_id, aruid, &surf));
	dbg_printf("opened managed layer");

	int64_t z;
  
	ASSERT_OK(fail_vi, vi_iads_set_layer_scaling_mode(2, &surf));
  
	ASSERT_OK(fail_vi, vi_imds_set_layer_visibility(true, &surf));
	ASSERT_OK(fail_vi, vi_isds_set_layer_visibility(true, &surf));
	  //ASSERT_OK(fail_vi, vi_isds_set_layer_size(&surf, 1280, 720));
  
	  /*dbg_printf("trying to add to layer stack(s)...");
	  for(int i = 0; i < 11; i++) {
	  dbg_printf("  stack %d: 0x%x", i, vi_imds_add_to_layer_stack(i, &surf));
	  }
	  //ASSERT_OK(fail_vi, vi_imds_set_display_layer_stack(0, &display));
	  ASSERT_OK(fail_vi, vi_imds_set_conductor_layer(true, &surf));
	  ASSERT_OK(fail_vi, vi_imds_set_content_visibility(true));*/
    
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

	if(status != 0) {
		printf("IGBP_CONNECT failure\n");
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

	printf("set z result : 0x%x\n", vi_isds_set_layer_z(&surf, 4));
	ASSERT_OK(fail_vi, vi_isds_get_layer_z(&surf, &z));
	printf("z: %ld\n", z);
  
	//int64_t zc_min, zc_max;
	//ASSERT_OK(fail_vi, vi_isds_get_z_order_count_min(&surf, &zc_min));
	//ASSERT_OK(fail_vi, vi_isds_get_z_order_count_max(&surf, &zc_max));
	//printf("z order min, max: %ld, %ld\n", zc_min, zc_max);
  
	printf("probing layers...\n");
	for(int i = 0; i < surf.layer_id; i++) {
		surface_t fake;
		fake.layer_id = i;
		r = vi_isds_get_layer_z(&fake, &z);
		if(r) {
			printf("%d: error 0x%x\n", i, r);
		} else {
			printf("%d: z %ld\n", i, z);
			/*if(i != 6) {
			  ASSERT_OK(fail_vi, vi_isds_set_layer_visibility(false, &fake));
			  ASSERT_OK(fail_vi, vi_imds_set_layer_visibility(false, &fake));
			  printf("  => disabled\n");
			  } else {
			  ASSERT_OK(fail_vi, vi_isds_set_layer_visibility(true, &fake));
			  ASSERT_OK(fail_vi, vi_imds_set_layer_visibility(true, &fake));
			  printf("  => enabled\n");
			  }*/
			//printf("  pos: 0x%x\n", vi_isds_set_layer_position(0.0f, 0.0f, &fake));
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
			printf("IGBP_DEQUEUE_BUFFER failure: %d\n", status);
			goto fail_vi;
		}
    
		printf("IGBP_DEQUEUE_BUFFER:\n");
		printf("  status: %d\n", status);
		printf("  slot: %d\n", slot);
		printf("  fence:\n");
		hexdump(&fence, sizeof(fence));
		printf("(hexdump end)\n");
    
		if(!requested[slot]) {
			graphic_buffer_t graphic_buffer_rq;
			ASSERT_OK(fail_vi, surface_request_buffer(&surf, slot, &status, &graphic_buffer_rq));
			if(status != 0) {
				printf("IGBP_REQUEST_BUFFER failure: %d\n", status);
				goto fail_vi;
			}
			printf("IGBP_REQUEST_BUFFER:\n");
			printf("  status: %d\n", status);

			memory_info_t meminfo;
			uint32_t pageinfo;
			ASSERT_OK(fail_vi, svcQueryMemory(&meminfo, &pageinfo, gpu_buffer_memory));
			printf("gpu buffer dev refcount: %d\n", meminfo.device_ref_count);
			printf("gpu buffer size: 0x%lx (should be 0x%lx)\n", meminfo.size, sizeof(gpu_buffer_memory));
      
			requested[slot] = true;
		}

		//memset(gpu_buffer_memory, 0xff, sizeof(gpu_buffer_memory));
		printf("gpubm+0x1000\n");
		hexdump(gpu_buffer_memory + 0x1000, 0x20);
    
		fence_t tfence = {{0x1, 0x25, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
		qbi.fence = tfence;

		ASSERT_OK(fail_vi, surface_queue_buffer(&surf, slot, &qbi, &qbo, &status));
		printf("IGBP_QUEUE_BUFFER:\n");
		printf("  status: %d\n", status);
		printf("  qbo:\n");
		printf("    width: %d\n", qbo.width);
		printf("    height: %d\n", qbo.height);
		printf("    transform_hint: %d\n", qbo.transform_hint);
		printf("    num_pending_buffers: %d\n", qbo.num_pending_buffers);
		if(status != 0) {
			printf("IGBP_QUEUE_BUFFER failure: %d\n", status);
			goto fail_vi;
		}
		qbi.timestamp+= 0x100;

		printf("done with frame %d\n", i);
    
		printf("i sleep\n");
		svcSleepThread(1000000000);
		printf("woke\n");
	}
  
fail_vi:
	vi_finalize();
fail_gpu:
	gpu_finalize();
fail_am:
	am_finalize();
fail_sm:
	sm_finalize();
fail:
	return r != RESULT_OK;
}
