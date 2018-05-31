#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/ipc/ro.h>

#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>
#include<libtransistor/ld/module.h>
#include<libtransistor/ld/internal.h>
#include<libtransistor/ld/loaders.h>

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

static const ld_loader_t *loaders[] = {
	&ld_loader_nro_via_svc,
	&ld_loader_nro_via_ldr_ro,
	&ld_loader_elf,
};

result_t ld_load_module(FILE *f, const char *name_src, module_t **out, bool is_global) {
	if(fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
	}

	ssize_t file_size = ftell(f);
	if(file_size == -1) {
		fclose(f);
		return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
	}

	if(fseek(f, 0, SEEK_SET) != 0) {
		fclose(f);
		return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
	}

	void *file_buffer = alloc_pages(file_size, file_size, NULL);
	if(file_buffer == NULL) {
		fclose(f);
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
		
	ssize_t total_read = 0;
	while(total_read < file_size) {
		size_t r = fread(file_buffer + total_read, 1, file_size - total_read, f);
		if(r == 0) {
			free_pages(file_buffer);
			fclose(f);
			return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_READ_MODULE;
		}
		total_read+= r;
	}
	fclose(f);

	module_input_t input;
	input.name = name_src;
	input.has_run_basic_relocations = false;
	input.is_global = is_global;
	
	result_t results[ARRAY_LENGTH(loaders)];
	for(size_t i = 0; i < ARRAY_LENGTH(loaders); i++) {
		results[i] = loaders[i]->can_load(file_buffer, file_size);
		if(results[i] == RESULT_OK) {
			result_t r;
			if((r = loaders[i]->load(&input, file_buffer, file_size)) != RESULT_OK) {
				free_pages(file_buffer);
				return r;
			}
			return ld_add_module(input, out);
		}
	}
	return LIBTRANSISTOR_ERR_TRNLD_NO_LOADER_FOR_MODULE;
}

result_t ld_discover_module(const char *name_src, module_t **out, bool is_global) {
	char name[0x301];
	strncpy(name, name_src, 0x29C);
	name[0x300] = 0;

	int len = strlen(name);
	
	for(int i = 0; i < len; i++) {
		if(name[i] == '/') {
			FILE *f = fopen(name, "rb");
			if(f == NULL) {
				return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_FIND_MODULE;
			}
			return ld_load_module(f, name_src, out, is_global);
		}
	}
	
	char path[0x301];
	for(uint64_t i = 0; i < ARRAY_LENGTH(ld_search_path); i++) {
		strncpy(path, ld_search_path[i], 0x300);
		path[0x300] = 0;
		int len = strlen(path);
		strncpy(path + len, name, 0x300-len);
		path[0x300] = 0;
		
		FILE *f = fopen(path, "rb");
		if(f == NULL) {
			continue;
		}

		return ld_load_module(f, name_src, out, is_global);
	}

	// try stripping .so suffix
	if(strcmp(name + len - 3, ".so") == 0) {
		len-= 3;
		name[len] = 0;
		return ld_discover_module(name, out, is_global);
	}

	// try appending .nro if it's not already there
	if(strcmp(name + len - 4, ".nro") != 0) {
		strcat(name, ".nro");
		return ld_discover_module(name, out, is_global);
	} else {
		return LIBTRANSISTOR_ERR_TRNLD_FAILED_TO_FIND_MODULE;
	}
}
