#include<libtransistor/ld/loaders.h>

#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/address_space.h>
#include<libtransistor/loader_config.h>
#include<libtransistor/svc.h>

#include<libtransistor/ld/ld.h>

#include<string.h>
#include<stdlib.h>

typedef struct {
	uint32_t file_offset;
	uint32_t size;
} segment_header_t;

typedef struct {
	uint32_t jump;
	uint32_t mod_offset;
	uint32_t padding1[2];
	uint32_t magic;
	uint32_t unknown1;
	uint32_t size;
	uint32_t unknown2;
	segment_header_t segments[3];
	uint32_t bss_size;
} nro_header_t;

typedef struct {
	void *nro_image;
	void *nro_bss;
	size_t image_size;
	size_t bss_size;
} ld_nro_via_svc_data;

static result_t reprotect_segment(void *load_base, segment_header_t segment, int permission) {
	return svcSetProcessMemoryPermission(loader_config.process_handle, (uint64_t) load_base + segment.file_offset, segment.size, permission);
}

static const uint8_t required_syscalls[] = {
	SVC_ID_SET_PROCESS_MEMORY_PERMISSION,
	SVC_ID_MAP_PROCESS_CODE_MEMORY,
	SVC_ID_UNMAP_PROCESS_CODE_MEMORY,
	0
};

static result_t ld_nro_via_svc_can_load(void *file, size_t file_size) {
	if(!loader_config.has_process_handle) {
		return LIBTRANSISTOR_ERR_TRNLD_NEEDS_PROCESS_HANDLE;
	}
	result_t r;
	if((r = lconfig_has_syscalls(required_syscalls)) != RESULT_OK) {
		return r;
	}
	if(file_size < sizeof(nro_header_t)) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_NRO;
	}
	nro_header_t head = *(nro_header_t*) file;
	if(head.magic != 0x304f524e) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_NRO;
	}
	if(file_size & 0xFFF) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_NRO;
	}
	if(head.bss_size & 0xFFF) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_NRO;
	}
	return RESULT_OK;
}

static result_t ld_nro_via_svc_load(module_input_t *spec_out, void *nro_image, size_t nro_image_size) {
	result_t r;
	nro_header_t head = *(nro_header_t*) nro_image;
	if((r = ld_nro_via_svc_can_load(nro_image, nro_image_size)) != RESULT_OK) {
		return r;
	}

	void *load_base = as_reserve(nro_image_size + head.bss_size);
	void *nro_bss = alloc_pages(head.bss_size, head.bss_size, NULL);
	if(nro_bss == NULL) {
		r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		goto fail_load_base;
	}
	memset(nro_bss, 0, head.bss_size);

	ld_nro_via_svc_data *loader_data = malloc(sizeof(*loader_data));
	if(loader_data == NULL) {
		r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		goto fail_bss;
	}
	loader_data->nro_image = nro_image;
	loader_data->nro_bss = nro_bss;
	loader_data->image_size = nro_image_size;
	loader_data->bss_size = head.bss_size;
	
	LIB_ASSERT_OK(fail_bss, svcMapProcessCodeMemory(loader_config.process_handle, load_base, nro_image, nro_image_size));
	LIB_ASSERT_OK(fail_main_map, svcMapProcessCodeMemory(loader_config.process_handle, load_base + nro_image_size, nro_bss, head.bss_size));

	
	LIB_ASSERT_OK(fail_bss_map, reprotect_segment(load_base, head.segments[0], 5)); // .text is RX
	LIB_ASSERT_OK(fail_bss_map, reprotect_segment(load_base, head.segments[1], 1)); // .rodata is R
	LIB_ASSERT_OK(fail_bss_map, reprotect_segment(load_base, head.segments[2], 3)); // .data is RW
	LIB_ASSERT_OK(fail_bss_map, svcSetProcessMemoryPermission(loader_config.process_handle, (uint64_t) load_base + head.segments[2].file_offset + head.segments[2].size, head.bss_size, 3)); // .bss is RW
	
	spec_out->base = load_base;
	spec_out->loader = &ld_loader_nro_via_svc;
	spec_out->loader_data = loader_data;
	return RESULT_OK;
	
fail_bss_map:
	svcUnmapProcessCodeMemory(loader_config.process_handle, load_base + nro_image_size, nro_bss, head.bss_size);
fail_main_map:
	svcUnmapProcessCodeMemory(loader_config.process_handle, load_base, nro_image, nro_image_size);
	free(loader_data);
fail_bss:
	free_pages(nro_bss);
fail_load_base:
	as_release(load_base, nro_image_size + head.bss_size);
	return r;
}

static result_t result_or(result_t a, result_t b) {
	if(a != RESULT_OK) {
		return a;
	} else {
		return b;
	}
}

static result_t ld_nro_via_svc_unload(module_input_t *spec) {
	result_t r = RESULT_OK;
	ld_nro_via_svc_data *loader_data = spec->loader_data;
	r = result_or(r, svcUnmapProcessCodeMemory(loader_config.process_handle, spec->base + loader_data->image_size, loader_data->nro_bss, loader_data->bss_size));
	r = result_or(r, svcUnmapProcessCodeMemory(loader_config.process_handle, spec->base, loader_data->nro_image, loader_data->image_size));
	free(loader_data);
	return r;
}

ld_loader_t ld_loader_nro_via_svc = {
	.can_load = ld_nro_via_svc_can_load,
	.load = ld_nro_via_svc_load,
	.unload = ld_nro_via_svc_unload,
};
