#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/ipc/ro.h>

#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>
#include<libtransistor/ld/module.h>
#include<libtransistor/ld/internal.h>
#include<libtransistor/ld/loader/nro_via_ldr_ro.h>

#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>

static const char *ld_search_path[] = {
	"/sd/lib/",
	"/squash/lib/",
	"/sd/",
	"/squash/",
};

result_t ld_load_module(FILE *f, const char *name_src, module_t **out) {
	if(fseek(f, 0, SEEK_END) != 0) {
		dbg_printf("fseek failure");
		fclose(f);
		return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
	}

	ssize_t file_size = ftell(f);
	if(file_size == -1) {
		dbg_printf("ftell failure");
		fclose(f);
		return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
	}

	if(fseek(f, 0, SEEK_SET) != 0) {
		dbg_printf("fseek failure");
		fclose(f);
		return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
	}

	void *file_buffer = alloc_pages(file_size, file_size, NULL);
	if(file_buffer == NULL) {
		dbg_printf("failed to allocate space for library");
		fclose(f);
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
		
	ssize_t total_read = 0;
	while(total_read < file_size) {
		size_t r = fread(file_buffer + total_read, 1, file_size - total_read, f);
		if(r == 0) {
			dbg_printf("failed to read file (read 0x%x/0x%x bytes): %d", total_read, file_size, errno);
			free_pages(file_buffer);
			fclose(f);
			return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
		}
		total_read+= r;
	}
	fclose(f);

	module_input_t input;
	input.name = name_src;
	
	if(file_size >= 0x14 && memcmp(file_buffer + 0x10, "NRO0", 4) == 0) {
		result_t r;
		if((r = ld_nro_via_ldr_ro_load(&input, file_buffer, file_size)) != RESULT_OK) {
			free_pages(file_buffer);
			return r;
		}
	} else {
		return LIBTRANSISTOR_ERR_TRNLD_NO_LOADER_FOR_MODULE;
	}
	
	return ld_add_module(input, out);
}

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

	for(int i = 0; i < len; i++) {
		if(name[i] == "/") {
			FILE *f = fopen(name, "rb");
			if(f == NULL) {
				return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_FIND_MODULE;
			}
			return ld_load_module(f, name_src, out);
		}
	}
	
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

		return ld_load_module(f, name_src, out);
	}
	return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_FIND_MODULE;
}
