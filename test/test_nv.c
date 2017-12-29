#include<libtransistor/nx.h>

#include<string.h>
#include<malloc.h>
#include<stdio.h>

#include "test_nv_ioc_templates.h"

int test_template(const char *name, int fd, int rq, void *buffer, const void *template, size_t size, int initialize, int retcode) {
	int alloc_buf = 0;
	if(buffer == NULL) {
		buffer = malloc(size);
		alloc_buf = 1;
		if(!initialize) {
			memset(buffer, 0, size);
		}
	}
	if(initialize) {
		if(template != NULL) {
			memcpy(buffer, template, size);
		} else {
			memset(buffer, 0, size);
		}
	}
	int e;
	if((e = nv_ioctl(fd, rq, buffer, size)) != retcode) {
		printf("failed %s: %d, 0x%x, %d\n", name, e, nv_result, nv_errno);
		return 1;
	}
	if(template != NULL) {
		if(memcmp(buffer, template, size) != 0) {
			printf("failed %s: didn't match template\n", name);
			printf("template:\n");
			hexdump(template, size);
			printf("result:\n");
			hexdump(buffer, size);
			return 1;
		}
	}
	if(alloc_buf) {
		free(buffer);
	}
	return 0;
}

int main() {
	svcSleepThread(100000000);
  
	result_t r;
	if((r = sm_init()) != RESULT_OK) {
		printf("failed to init sm: 0x%x\n", r);
		return 1;
	}

	if((r = nv_init()) != RESULT_OK) {
		printf("failed to init nv: 0x%x, %d\n", r, nv_errno);
		goto err_only_sm;
	}

	int nvhcg = nv_open("/dev/nvhost-ctrl-gpu");
	if(nvhcg < 0) {
		printf("failed to open /dev/nvhost-ctrl-gpu\n");
		goto err_nv;
	}
	printf("opened /dev/nvhost-ctrl-gpu: 0x%x\n", nvhcg);


  
	struct {
		uint64_t bufsz;
		uint64_t bufaddr;
		uint8_t characteristics[0xa0];  
	} ioctl_args;
	ioctl_args.bufsz = 0xa0;
	ioctl_args.bufaddr = 1;
	if(test_template("GET_CHARACTERISTICS", nvhcg, 0xc0b04705, &ioctl_args, NULL, sizeof(ioctl_args), 0, 0)) { goto err_nvhost_ctrl_gpu; } // TODO: make template for this to check against


  
	int nvhc = nv_open("/dev/nvhost-ctrl");
	if(nvhc < 0) {
		printf("failed to open /dev/nvhost-ctrl\n");
		goto err_nvhost_ctrl_gpu;
	}
	printf("opened /dev/nvhost-ctrl: 0x%d\n", nvhcg);


  
	/*if(test_template("GET_CONFIG 1", nvhc, 0xc183001b, NULL, get_config_template, sizeof(get_config_template), 1, 11)) { goto err_nvhost_ctrl; }
	  if(test_template("GET_CONFIG 2", nvhc, 0xc183001b, NULL, get_config_template_2, sizeof(get_config_template_2), 1, 11)) { goto err_nvhost_ctrl; }*/
	uint32_t zcull_ctx_size_template = 0x10200;
	if(test_template("GET_ZCULL_CTX_SIZE", nvhcg, 0x80044701, NULL, &zcull_ctx_size_template, sizeof(zcull_ctx_size_template), 0, 0)) { goto err_nvhost_ctrl; }
	if(test_template("ZCULL_GET_INFO", nvhcg, 0x80284702, NULL, &zcull_get_info_template, sizeof(zcull_get_info_template), 0, 0)) { goto err_nvhost_ctrl; }

  

	int nvhag = nv_open("/dev/nvhost-as-gpu");
	if(nvhag < 0) {
		printf("failed to open /dev/nvhost-as-gpu\n");
		goto err_nvhost_ctrl;
	}
	printf("opened /dev/nvhost-as-gpu: 0x%d\n", nvhag);

	uint32_t nvhag_init_rq[] = {0x10000, 0x0, 0x0, 0x0};
	uint32_t nvhag_init_rs[] = {    0x0, 0x0, 0x0, 0x0};
	if(test_template("NVGPU_AS_INITIALIZE", nvhag, 0x40104107, &nvhag_init_rq, &nvhag_init_rs, sizeof(nvhag_init_rs), 0, 0)) { goto err_nvhost_as_gpu; }
	if(test_template("GET_VA_REGIONS(0)", nvhag, 0xc0404108, NULL, nvhag_get_va_regs_0_template, sizeof(nvhag_get_va_regs_0_template), 0, 0)) { goto err_nvhost_as_gpu; }
	if(test_template("GET_VA_REGIONS(2)", nvhag, 0xc0404108, nvhag_get_va_regs_2_rq, nvhag_get_va_regs_2_template, sizeof(nvhag_get_va_regs_2_template), 0, 0)) { goto err_nvhost_as_gpu; }
	if(test_template("ALLOC_SPACE", nvhag, 0xc0184102, nvhag_alloc_space_rq, nvhag_alloc_space_template, sizeof(nvhag_alloc_space_template), 0, 0)) { goto err_nvhost_as_gpu; }



	int nvmap = nv_open("/dev/nvmap");
	if(nvmap < 0) {
		printf("failed to open /dev/nvmap\n");
		goto err_nvhost_as_gpu;
	}
	printf("opened /dev/nvmap: 0x%d\n", nvmap);

	struct nvmap_create_args {
		uint32_t size;   // in
		uint32_t handle; // out
	};
	struct nvmap_create_args nvmc;
	nvmc.size = 0x1000;
	nvmc.handle = 0;
	int e = nv_ioctl(nvmap, 0xc0080101, &nvmc, sizeof(nvmc));
	if(e != 0) {
		printf("failed NVMAP_CREATE: %d, 0x%x, %d\n", e, nv_result, nv_errno);
		goto err_nvmap;
	}
	if(nvmc.size != 0x1000) {
		printf("nvmc size changed\n");
		goto err_nvmap;
	}

	int nvmap_handle = nvmc.handle;
	printf("got nvmap handle: 0x%x\n", nvmap_handle);

	struct nvmap_alloc_args {
		uint32_t handle;
		uint32_t heapmask;
		uint32_t flags;
		uint32_t align;
		uint8_t kind;
		uint8_t padding[7];
		uint64_t addr;
	};
	struct nvmap_alloc_args nvma_t;
	nvma_t.handle = nvmap_handle;
	nvma_t.heapmask = 0;
	nvma_t.flags = 0;
	nvma_t.align = 0x20000;
	nvma_t.kind = 0;
	nvma_t.addr = 0xaa0035000;
	if(test_template("NVMAP_ALLOC", nvmap, 0xc0200104, NULL, &nvma_t, sizeof(nvma_t), 1, 0)) {
		goto err_nvmap;
	}

	printf("test NVAS_MAP_BUFFER_EX\n");
	nvasmbe.flags = 0;
	nvasmbe.kind = 0;
	nvasmbe.nvmap_handle = nvmap_handle;
	nvasmbe.page_size = 0x10000;
	nvasmbe.buffer_offset = 0;
	nvasmbe.mapping_size = 0;
	nvasmbe.offset = 0;
	nvasmbe_t.offset = 0x500000000;
	if(test_template("NVAS_MAP_BUFFER_EX", nvhag, 0xc0284106, &nvasmbe, NULL, sizeof(nvasmbe), 0, 0)) {
		goto err_nvmap;
	}

  
	printf("everything passes\n");

err_nvmap:
	if(nv_close(nvmap) != 0) {
		printf("failed to close /dev/nvmap\n");
		goto err_nvmap;
	}
err_nvhost_as_gpu:
	if(nv_close(nvhag) != 0) {
		printf("failed to close /dev/nvhost-as-gpu\n");
		goto err_nvhost_ctrl;
	}
err_nvhost_ctrl:
	if(nv_close(nvhc) != 0) {
		printf("failed to close /dev/nvhost-ctrl\n");
		goto err_nvhost_ctrl_gpu;
	}
err_nvhost_ctrl_gpu:
	if(nv_close(nvhcg) != 0) {
		printf("failed to close /dev/nvhost-ctrl-gpu\n");
		goto err_nv;
	}
err_nv:
	nv_finalize();
err_only_sm:
	sm_finalize();

	return 0;
}
