#include<stdio.h>
#include<dlfcn.h>

int main(int argc, char *argv[]) {
	void *handle = dlopen("libdynamic_dlobj.nro", RTLD_LOCAL);
	if(handle == NULL) {
		printf("failed to dlopen: %s\n", dlerror());
	}
	int (*func)(int) = dlsym(handle, "func");
	if(func == NULL) {
		printf("failed to dlsym: %s\n", dlerror());
	}
	int ret = func(6);
	printf("func(6) -> %d\n", ret);
	if(ret != 6 * 8) {
		return 1;
	}
	return dlclose(handle);
}
