#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/ipc/ro.h>

#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/loaders.h>

#include<sha256.h>
#include<stdlib.h>

const size_t NRR_SIZE = 0x1000;

typedef struct {
	void *nro_image;
	void *nrr;
	void *bss;
} ld_nro_via_ldr_ro_data;

static result_t ld_nro_via_ldr_ro_can_load(void *file, size_t file_size) {
	if(file_size < 0x40) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_NRO;
	}
	if(*((uint32_t*) (file + 0x10)) != 0x304f524e) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_NRO;
	}
	return RESULT_OK;
}

static result_t ld_nro_via_ldr_ro_load(module_input_t *spec_out, void *nro_image, size_t nro_image_size) {
	if(nro_image_size < 0x40) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_NRO;
	}

	result_t r;

	ld_nro_via_ldr_ro_data *loader_data = malloc(sizeof(*loader_data));
	
	uint32_t *nrr = alloc_pages(NRR_SIZE, NRR_SIZE, NULL);
	if(nrr == NULL) {
		r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		goto fail_loader_data;
	}
	nrr[0] = 0x3052524E; // NRR0
	nrr[(0x338 >> 2) + 0] = NRR_SIZE;
	nrr[(0x340 >> 2) + 0] = 0x350; // hash offset
	nrr[(0x340 >> 2) + 1] = 0x1; // hash count

	SHA256_CTX ctx;
	sha256_init(&ctx);
	sha256_update(&ctx, (uint8_t*) nro_image, nro_image_size);
	sha256_final(&ctx, (uint8_t*) &nrr[0x350 >> 2]); // hash
	
	uint32_t nro_bss_size = *(uint32_t*)(nro_image + 0x38);
	void *nro_bss = alloc_pages(nro_bss_size, nro_bss_size, NULL);
	if(nro_bss == NULL) {
		r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		goto fail_nrr;
	}
	
	if((r = ro_init()) != RESULT_OK) {
		goto fail_bss;
	}
	
	if((r = ro_load_nrr(nrr, NRR_SIZE)) != RESULT_OK) {
		goto fail_ro;
	}
	
	void *nro_base;
	if((r = ro_load_nro(&nro_base, nro_image, nro_image_size, nro_bss, nro_bss_size)) != RESULT_OK) {
		goto fail_loaded_nrr;
	}
	
	loader_data->nro_image = nro_image;
	loader_data->bss = nro_bss;
	loader_data->nrr = nrr;
	spec_out->base = nro_base;
	spec_out->loader = &ld_loader_nro_via_ldr_ro;
	spec_out->loader_data = loader_data;
	return RESULT_OK;

fail_loaded_nrr:
	ro_unload_nrr(nrr);
fail_ro:
	ro_finalize();
fail_bss:
	free_pages(nro_bss);
fail_nrr:
	free_pages(nrr);
fail_loader_data:
	free(loader_data);
	return r;
}

static result_t ld_nro_via_ldr_ro_unload(module_input_t *spec) {
	result_t r;
	ld_nro_via_ldr_ro_data *loader_data = spec->loader_data;
	r = ro_unload_nro(spec->base, loader_data->nro_image);
	if(r == RESULT_OK) {
		r = ro_unload_nrr(loader_data->nrr);
	}
	free_pages(loader_data->nrr);
	free_pages(loader_data->nro_image);
	free_pages(loader_data->bss);
	free(loader_data);
	return r;
}

ld_loader_t ld_loader_nro_via_ldr_ro = {
	.can_load = ld_nro_via_ldr_ro_can_load,
	.load = ld_nro_via_ldr_ro_load,
	.unload = ld_nro_via_ldr_ro_unload,
};
