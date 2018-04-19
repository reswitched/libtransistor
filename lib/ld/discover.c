#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/ipc/ro.h>

#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>
#include<libtransistor/ld/module.h>
#include<libtransistor/ld/internal.h>

#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>

static const char *ld_search_path[] = {
	"/sd/lib/",
	"/squash/lib/",
	"/squash/",
};

result_t ld_discover_module(const char *name_src, module_t **out) {
	dbg_printf("discovering %s", name_src);
	char name[0x301];
	strncpy(name, name_src, 0x300);
	name[0x300] = 0;

	int len = strlen(name);
	// strip .so suffix
	if(strcmp(name + len - 3, ".so") == 0) {
		len-= 3;
		name[len] = 0;
	}
	dbg_printf("transformed to %s", name);

	char path[0x301];
	for(uint64_t i = 0; i < ARRAY_LENGTH(ld_search_path); i++) {
		strncpy(path, ld_search_path[i], 0x300);
		path[0x300] = 0;
		int len = strlen(path);
		strncpy(path + len, name, 0x300-len);
		path[0x300] = 0;
		
		dbg_printf("try %s", path);
		FILE *f = fopen(path, "rb");
		if(f == NULL) {
			continue;
		}
		dbg_printf("got %s", path);
		if(fseek(f, 0, SEEK_END) != 0) {
			dbg_printf("fseek failure");
			fclose(f);
			continue;
		}
		ssize_t nro_size = ftell(f);
		if(nro_size == -1) {
			dbg_printf("ftell failure");
			fclose(f);
			continue;
		}
		if(fseek(f, 0, SEEK_SET) != 0) {
			dbg_printf("fseek failure");
			fclose(f);
			continue;
		}
		
		void *nro_buffer = alloc_pages(nro_size, nro_size, NULL);
		if(nro_buffer == NULL) {
			dbg_printf("failed to allocate space for nro");
			fclose(f);
			return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		}
		ssize_t total_read = 0;
		while(total_read < nro_size) {
			size_t r = fread(nro_buffer + total_read, 1, nro_size - total_read, f);
			if(r == 0) {
				dbg_printf("failed to read nro (read 0x%x/0x%x bytes): %d", total_read, nro_size, errno);
				free_pages(nro_buffer);
				fclose(f);
				return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
			}
			total_read+= r;
		}

		fclose(f);

		uint32_t nro_bss_size = *(uint32_t*)(nro_buffer + 0x38);
		void *nro_bss = alloc_pages(nro_bss_size, nro_bss_size, NULL);
		if(nro_bss == NULL) {
			dbg_printf("failed to allocate bss");
			free_pages(nro_buffer);
			return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		}
		
		result_t r;
		if((r = ro_init()) != RESULT_OK) {
			dbg_printf("failed to init ro");
			free_pages(nro_bss);
			free_pages(nro_buffer);
			return r;
		}

		// TODO: load NRR, modular loaders
		
		void *nro_base;
		if((r = ro_load_nro(&nro_base, nro_buffer, nro_size, nro_bss, nro_bss_size)) != RESULT_OK) {
			free_pages(nro_bss);
			free_pages(nro_buffer);
			return r;
		}

		dbg_printf("loaded NRO @ %p", nro_base);
		
		module_input_t input;
		input.name = name_src;
		input.base = nro_base;
		input.type = MODULE_TYPE_NRO_VIA_LDR_RO;
		input.nro_via_ldr_ro.nro_image = nro_buffer;
		input.nro_via_ldr_ro.bss = nro_bss;
		return ld_add_module(input, out);
	}
	return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_FIND_MODULE;
}
