#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/ipc/ro.h>

#include<libtransistor/ld/ld.h>

result_t ld_nro_via_ldr_ro_load(module_input_t *spec_out, void *nro_image, size_t nro_image_size) {
	if(nro_image_size < 0x40) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_NRO;
	}
	
	uint32_t nro_bss_size = *(uint32_t*)(nro_image + 0x38);
	void *nro_bss = alloc_pages(nro_bss_size, nro_bss_size, NULL);
	if(nro_bss == NULL) {
		dbg_printf("failed to allocate bss");
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	
	result_t r;
	if((r = ro_init()) != RESULT_OK) {
		dbg_printf("failed to init ro");
		free_pages(nro_bss);
		return r;
	}
	
	// TODO: load NRR
	
	void *nro_base;
	if((r = ro_load_nro(&nro_base, nro_image, nro_image_size, nro_bss, nro_bss_size)) != RESULT_OK) {
		free_pages(nro_bss);
		return r;
	}
	
	dbg_printf("loaded NRO @ %p", nro_base);
	
	spec_out->base = nro_base;
	spec_out->type = MODULE_TYPE_NRO_VIA_LDR_RO;
	spec_out->nro_via_ldr_ro.nro_image = nro_image;
	spec_out->nro_via_ldr_ro.bss = nro_bss;
	return RESULT_OK;
}

result_t ld_nro_via_ldr_ro_unload(module_input_t *spec) {
	result_t r;
	r = ro_unload_nro(spec->base, spec->nro_via_ldr_ro.nro_image);
	free_pages(spec->nro_via_ldr_ro.nro_image);
	free_pages(spec->nro_via_ldr_ro.bss);
	return r;
}
