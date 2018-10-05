#include<libtransistor/environment.h>

#include<libtransistor/svc.h>

void *env_stack_top;

kernel_version_t env_get_kernel_version() {
	static kernel_version_t version = KERNEL_VERSION_INVALID;
	if(version == KERNEL_VERSION_INVALID) {
		version = KERNEL_VERSION_MAX;
		uint64_t info;
		result_t r;
		if((r = svcGetInfo(&info, 20, 0xffffffff, 0)) == 0xf001) { version = KERNEL_VERSION_500 - 1; }
		if((r = svcGetInfo(&info, 19, 0xffffffff, 0)) == 0xf001) { // removed in 5.0.0
			if(version != KERNEL_VERSION_MAX) {
				version = KERNEL_VERSION_400 - 1;
			}
		}
		if((r = svcGetInfo(&info, 16, 0xffffffff, 0)) == 0xf001) { version = KERNEL_VERSION_300 - 1; }
		if((r = svcGetInfo(&info, 12, 0xffffffff, 0)) == 0xf001) { version = KERNEL_VERSION_200 - 1; }
	}
	return version;
}

void *env_get_stack_top() {
	return env_stack_top;
}
