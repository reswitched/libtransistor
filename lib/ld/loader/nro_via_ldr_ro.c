#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/ipc/ro.h>

#include<libtransistor/ld/ld.h>

#include<sha256.h>

const size_t NRR_SIZE = 0x1000;

result_t ld_nro_via_ldr_ro_load(module_input_t *spec_out, void *nro_image, size_t nro_image_size) {
	if(nro_image_size < 0x40) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_NRO;
	}

	result_t r;
	
	uint32_t *nrr = alloc_pages(NRR_SIZE, NRR_SIZE, NULL);
	if(nrr == NULL) {
		r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		goto fail;
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
		dbg_printf("failed to allocate bss");
		r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		goto fail_nrr;
	}
	
	if((r = ro_init()) != RESULT_OK) {
		dbg_printf("failed to init ro");
		goto fail_bss;
	}
	
	if((r = ro_load_nrr(nrr, NRR_SIZE)) != RESULT_OK) {
		goto fail_ro;
	}
	
	void *nro_base;
	if((r = ro_load_nro(&nro_base, nro_image, nro_image_size, nro_bss, nro_bss_size)) != RESULT_OK) {
		goto fail_loaded_nrr;
	}
	
	dbg_printf("loaded NRO @ %p", nro_base);
	
	spec_out->base = nro_base;
	spec_out->type = MODULE_TYPE_NRO_VIA_LDR_RO;
	spec_out->nro_via_ldr_ro.nro_image = nro_image;
	spec_out->nro_via_ldr_ro.bss = nro_bss;
	return RESULT_OK;

fail_loaded_nrr:
	ro_unload_nrr(nrr);
fail_ro:
	ro_finalize();
fail_bss:
	free_pages(nro_bss);
fail_nrr:
	free_pages(nrr);
fail:
	return r;
}

result_t ld_nro_via_ldr_ro_unload(module_input_t *spec) {
	result_t r;
	r = ro_unload_nro(spec->base, spec->nro_via_ldr_ro.nro_image);
	free_pages(spec->nro_via_ldr_ro.nro_image);
	free_pages(spec->nro_via_ldr_ro.bss);
	return r;
}
