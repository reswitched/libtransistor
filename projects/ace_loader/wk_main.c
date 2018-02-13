#include <libtransistor/nx.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "common_setup.h"
#include "memory.h"
#include "wk_memory.h"
#include "nro.h"

// thread context
typedef struct
{
	void *ptr_1c8;
	uint64_t unk0;
	void *ptr_10_a;
	void *ptr_10_b;
	uint8_t empty[0x20];
	uint32_t status;
	uint32_t priority;
	void *sp_base;
	void *sp_mirror;
	uint64_t sp_size;
	uint8_t unk1[0x128];
	char name[32];
	void *name_ptr;
	uint64_t unk2;
	uint32_t handle;
	uint32_t zero;
	void *mutex;
	uint64_t unk3;
} thread_context_t;

uint64_t extra_cleanup(uint64_t arg0);

// these handles seems to be always present
const int static_handles[] =
{
	0x010001,
	0x020003,
	0x028002,
	0x030004,
	0x038005,
	0x040006,
	0x048007,
	0x058009,
	0x06000A,
	0x06800B,
	0x07000C,
	0x08000E,
	0x08800D,
	0x09000F,
	0x098010,
	0x0A0011,
	0x0A8012,
	0x0B0013,
	0x0B8014,
	0x0C0015,
	0x100017,
	0x1E0016,
	0x1E8018,
	0x1F0019,
	0x1F801A,
	0x20001B,
	0x21001D,
	0x21801E,
	0x248021,
	0x25001F,
	0x290023,
	0x298022,
	0x2A0024,
	0x2A8025,
	0x2B0026,
	0x2C0028,
	0x2D802A,
	0x2E002B,
	0x2E802C,
	0x2F002D,
	0x2F802E,
	0x30802F,
	0x328032,
	0x330033,
	0x338034,
	0x348036
};

extern thread_h aceloader_main_thread_handle;

void locate_threads(void *base, uint64_t size, int simple)
{
	memory_info_t minfo;
	uint32_t pinfo;
	thread_context_t *tc;

	while(size)
	{
		tc = (thread_context_t*)*(uint64_t*)(base + 0x1f8);
		if(!svcQueryMemory(&minfo, &pinfo, tc) && minfo.permission == 3)
		{
			if(!svcGetThreadPriority(&pinfo, tc->handle))
			{
				printf("- found thread context 0x%016lX at 0x%016lX\n handle: 0x%08X\n SP base: 0x%016lX\n SP mirror: 0x%016lX\n SP size: 0x%016lX\n ptrs 0x%016lX 0x%016lX 0x%016lX\n name: '%.32s'\n", (uint64_t)tc, (uint64_t)base, tc->handle, (uint64_t)tc->sp_base, (uint64_t)tc->sp_mirror, tc->sp_size, (uint64_t)tc->ptr_1c8, (uint64_t)tc->ptr_10_a, (uint64_t)tc->ptr_10_b, tc->name);
				if(strcmp(tc->name, "MainThread"))
				{
					uint64_t *ptr = tc->sp_mirror;
					uint64_t sizE = tc->sp_size;
					aceloader_main_thread_handle = tc->handle;
					uint64_t *bend = wkBase + WK_SIZE;
					switch(simple)
					{
						case 1:
							printf("- cancel sync: 0x%06X\n", svcCancelSynchronization(tc->handle));
//							printf("- reset signal: 0x%06X\n", svcResetSignal(tc->handle));
							printf("- close handle: 0x%06X\n", svcCloseHandle(tc->handle));
							printf("- unmap stack: 0x%06X\n", svcUnmapMemory(tc->sp_mirror, tc->sp_base, tc->sp_size));
						break;
						case 0:
							// exit thread
							printf("- cleaning up\n");
							while(sizE)
							{
								if(*ptr >= (uint64_t)wkBase && *ptr < (uint64_t)bend)
									*ptr = (uint64_t)(wkBase + 0x3ed2d4);
								ptr++;
								sizE -= sizeof(uint64_t);
							}
						break;
					}
				}
			} else
				printf("- found dead thread '%.32s'\n", tc->name);
		} else
			printf("- no thread context at 0x%016lX\n", (uint64_t)tc);
		base += 0x200;
		size -= 0x200;
	}
}

int thread_scan(int simple)
{
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;

	printf("searching for threads ...\n");

	while(1)
	{
		if(svcQueryMemory(&minfo, &pinfo, addr))
			return 1;

		if(minfo.permission == 3 && minfo.memory_type == 12)
		{
			printf("- found TLS block\n");
			locate_threads(minfo.base_addr, minfo.size, simple);
		}

		addr = minfo.base_addr + minfo.size;
		if(!addr)
			break;
	}
	return 0;
}

uint64_t wk_call(uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t offs0, uint64_t offs1)
{
	uint64_t ret;
	uint64_t (*func)(uint64_t, uint64_t, uint64_t, uint64_t) = wkBase + offs0 + (offs1 << 16);

	printf("* calling 0x%lX\n", offs0 + (offs1 << 16));
	ret = func(arg0, arg1, arg2, arg3);
	printf("* returned\n");

	return ret;
}

void close_handles()
{
	int i;

	for(i = 0; i < sizeof(static_handles) / sizeof(int); i++)
	{
		int ret0, ret1, ret2;
		int handle = static_handles[i];
		ret2 = svcClearEvent(handle);
		ret1 = svcResetSignal(handle);
		ret0 = svcCloseHandle(handle);
		printf("- clear, reset, close handle 0x%06X: 0x%06X, 0x%06X, 0x%06X\n", handle, ret2, ret1, ret0);
	}
}

// we need to restore webkit's TLS before returning back to it,
// but needs ours back when we go back to hook_func
static uint8_t preserve_tls[0x200];

void hook_func(uint64_t arg0)
{
	uint64_t (*funcA)(uint64_t);
	void *ptr;
	int ret;

	memcpy(get_tls(), preserve_tls, 0x200);
	
	printf("** EXIT HOOK **\n");

	// do some webkit cleanup

	funcA = wkBase + 0x1D01C;
	arg0 = funcA(arg0);
//	printf("- returned from 0x1D01C\n");

	funcA = wkBase + 0x2080c;
	arg0 = funcA(arg0 + 0x10);
//	printf("- returned from 0x2080c\n");

	arg0 = extra_cleanup(arg0);
//	printf("* extra return 0x%016lX\n", arg0);
	// kill all threads
	thread_scan(0);
	svcSleepThread(1000*1000*1000);
	thread_scan(1);
	svcSleepThread(1000*1000*1000);

	// close some handles
	printf("- closing handles\n");
	close_handles();
	svcSleepThread(100*1000*1000);

	// use entire heap
	ret = svcSetHeapSize(&ptr, 0x18000000);
	printf("- set heap size 0x%06X at 0x%016lX\n", ret, (uint64_t)ptr);

	// cleanup the heap
	if(wk_mem_heap_cleanup())
	{
		printf("- failed to cleanup heap area\n");
		goto crash;
	}

	ret = mem_init();
	if(ret != 0) {
		printf("- failed to setup page allocator: %d\n", ret);
		goto crash;
	}
	common_begin_server();
crash:
	exit_loader();
}

void exit_loader()
{
	if(std_sck >= 0)
		bsd_close(std_sck);
	bsd_finalize();
	ro_finalize();

	svcSleepThread(1000*1000*1000);
	// CRASH
	*(uint64_t*)8 = 1;
	while(1);
}

int main(int argc, char **argv)
{
	int ret;
	ret = common_init(argc, argv);
	if(ret != 0) {
		return ret;
	}
	
	// locate and hook webkit
	printf("searching for webkit ...\n");
	if(wk_mem_install_hook(hook_func))
	{
		printf("- failed to locate webkit memories\n");
		bsd_close(std_sck);
		bsd_finalize();
		sm_finalize();
		return 1;
	}

	_crt0_kludge_skip_cleanup = true; // TODO: remove this ASAP
	memcpy(preserve_tls, get_tls(), 0x200);
	printf("- ready to exit\n");
	return 0;
}
