#include <libtransistor/types.h>
#include <libtransistor/svc.h>
#include <libtransistor/ipc/pm.h>
#include <libtransistor/loader_config.h>
#include <libtransistor/alloc_pages.h>

#include <stdio.h>
#include <setjmp.h>
#include <malloc.h>

#include "common_setup.h"
#include "memory.h"

static jmp_buf exit_loader_jmpbuf;

int main(int argc, char **argv) {
	int ret;
	if(setjmp(exit_loader_jmpbuf) == 0) {
		ret = common_init(0, NULL);
		if(ret != 0) {
			return ret;
		}

		/*ret = pm_init();
		if(ret != 0) {
			return ret;
		}
		printf("- terminating browser...\n");
		ret = pm_terminate_process_by_title_id(0x0100000000001011);
		printf("-   => 0x%x\n", ret);
		pm_finalize();*/

		printf("- acquiring heap...\n");
		void *ptr;
		size_t size = 0x18000000;
		do {
			ret = svcSetHeapSize(&ptr, size); // crank up the heap size
			size-= 0x20000;
		} while(ret != 0 && size > 0x100000);
		printf("- svcSetHeapSize -> 0x%x, %p\n", ret, ptr);
		if(ret != 0) {
			return ret;
		}

		ret = ap_init();
		if(ret != 0) {
			return ret;
		}
		common_begin_server();
	}
	
	return 0;
}

void exit_loader() {
	printf("- panicking\b");
	longjmp(exit_loader_jmpbuf, 1);
}
