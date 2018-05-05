/**
 * @file dlfcn.h
 * @brief Dynamic linking functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum {
	RTLD_LAZY,
	RTLD_NOW,
	RTLD_GLOBAL,
	RTLD_LOCAL,
};

int dlclose(void *handle);
char *dlerror(void);
void *dlopen(const char *path, int flags);
void *dlsym(void *handle, const char *symbol);

#ifdef __cplusplus
}
#endif
