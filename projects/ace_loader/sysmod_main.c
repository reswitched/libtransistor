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

		ret = ap_probe_full_address_space();
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
