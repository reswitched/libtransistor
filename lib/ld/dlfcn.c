#include<dlfcn.h>

#include<libtransistor/ld/internal.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>

#include<stdlib.h>
#include<stdio.h>

// TODO: thread safety
static char last_error_buffer[512];
static char *last_error = NULL;

typedef struct {
	module_t *module;
} dl_handle_t;

int dlclose(void *ptr) {
	dl_handle_t *handle = ptr;
	if(handle != NULL) {
		if(handle->module) {
			ld_decref_module(handle->module);
		}
		free(handle);
	}
	return 0;
}

char *dlerror(void) {
	char *e = last_error;
	last_error = NULL;
	return e;
}

void *dlopen(const char *path, int flags) {
	result_t r;
	dl_handle_t *handle = malloc(sizeof(*handle));
	if(handle == NULL) {
		r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		goto fail;
	}
	if(path == NULL) {
		handle->module = NULL;
		return handle;
	}
	LIB_ASSERT_OK(fail_handle, ld_discover_module(path, &handle->module, flags & RTLD_GLOBAL));
	LIB_ASSERT_OK(fail_module, ld_process_modules());

	return handle;
fail_module:
	ld_decref_module(handle->module);
fail_handle:
	free(handle);
fail:
	snprintf(last_error_buffer, sizeof(last_error_buffer), "result code 0x%x", r);
	last_error = last_error_buffer;
	return NULL;
}

void *dlsym(void *ptr, const char *symbol) {
	dl_handle_t *handle = ptr;
	result_t r;
	Elf64_Sym *def;
	module_t *def_mod;

	if(handle == NULL || handle->module == NULL) {
		r = ld_resolve_load_symbol(symbol, &def, &def_mod);
	} else {
		r = ld_resolve_dependency_symbol(handle->module, symbol, &def, &def_mod);
	}
	if(r != RESULT_OK) {
		snprintf(last_error_buffer, sizeof(last_error_buffer), "result code 0x%x", r);
		last_error = last_error_buffer;
		return NULL;
	} else {
		return def_mod->input.base + def->st_value;
	}
}
