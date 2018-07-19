#include<libtransistor/environment.h>
#include<libtransistor/svc.h>

kernel_version_t env_get_kernel_version() {
	static kernel_version_t version = KERNEL_VERSION_INVALID;
	if(version == KERNEL_VERSION_INVALID) {
		version = KERNEL_VERSION_500;
		uint64_t info;
		if(svcGetInfo(&info, 20, 0xffff8001, 0) == 0xf001) { version = KERNEL_VERSION_500 - 1; }
		if(svcGetInfo(&info, 19, 0xffff8001, 0) == 0xf001) { version = KERNEL_VERSION_400 - 1; }
		if(svcGetInfo(&info, 16, 0xffff8001, 0) == 0xf001) { version = KERNEL_VERSION_300 - 1; }
		if(svcGetInfo(&info, 12, 0xffff8001, 0) == 0xf001) { version = KERNEL_VERSION_200 - 1; }
	}
	return version;
}
