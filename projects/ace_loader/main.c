#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
#include "memory.h"
#include "http.h"
#include "server.h"
#include "nro.h"

FILE custom_stdout;
int std_sck;

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

struct sockaddr_in stdout_server_addr =
{
	.sin_family = AF_INET,
	.sin_port = htons(STDOUT_PORT),
};

thread_h ACELOADER_MAIN_THREAD_HANDLE;

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

static int stdout_debug(struct _reent *reent, void *v, const char *ptr, int len)
{
	if(std_sck < 0)
		return len;
	bsd_send(std_sck, ptr, len, 0);
	return len;
}

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
					ACELOADER_MAIN_THREAD_HANDLE = tc->handle;
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
							// broken getInfo workaround
							if(tc->sp_mirror != tc->sp_base)
							{
								// use lowest detected mirror address
								if((uint64_t)tc->sp_mirror < (uint64_t)map_base)
									map_base = tc->sp_mirror;
							}
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

void hook_func(uint64_t arg0)
{
	uint64_t (*funcA)(uint64_t);
	void *ptr;
	int ret;

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

	// get map range - returns invalid range
	ret = svcGetInfo((uint64_t*)&map_base, 2, 0xffff8001, 0);
	if(!ret)
	{
		printf("- map base address 0x%016lX\n", (uint64_t)map_base);
	} else
		printf("- get info error 0x%06X\n", ret);

	ret = svcGetInfo((uint64_t*)&ptr, 3, 0xffff8001, 0);
	if(!ret)
	{
		printf("- map base size 0x%016lX\n", (uint64_t)ptr);
	} else
		printf("- get info error 0x%06X\n", ret);

	// broken getInfo workaround
	// lowest stack mirror found is used as actual base
	map_base = (void*)0xffffffffffffffff; 

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
	if(mem_heap_cleanup())
	{
		printf("- failed to cleanup heap area\n");
		goto crash;
	}

	// get largest heap block
	if(mem_get_heap())
	{
		printf("- failed to locate usefull heap area\n");
		goto crash;
	}

	// initialize RO
	ret = ro_init();
	if(ret)
	{
		printf("- ldr:ro initialization error 0x%06X\n", ret);
		goto crash;
	}

	// release sm; it's not needed anymore
	sm_finalize();

	// debug
	printf("- got %luB heap block at 0x%016lX\n", heap_size, (uint64_t)heap_base);

	// start autorun NRO - if found
	ret = http_get_file("autorun.nro", heap_base, heap_size);
	if(ret > 0)
	{
		uint64_t r;
		printf("- starting autorun\n");
		nro_arg_name("autorun");
		nro_add_arg(http_hostname);
		r = nro_execute(heap_base, ret);
		printf("- NRO returned 0x%016lX\n", r);
		// do not exit for GUIs
		if(!nro_loaded_count || nro_unload_fail)
			goto crash;
	}

	// start 'push' server
	if(!server_init())
		server_loop();

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
	const char *hostname;

	if(argc == 0)
		hostname = "a.b"; // PegaSwitch will respond to any DNS request
	else
		hostname = argv[0]; // use provided hostname

	ipc_debug_flag = 0;

	if(sm_init() != RESULT_OK)
		return 1;

	if(bsd_init() != RESULT_OK)
	{
		sm_finalize();
		return 1;
	}

	// init HTTP (resolve hostname)
	if(http_init(hostname))
	{
		bsd_close(std_sck);
		bsd_finalize();
		sm_finalize();
		return 1;
	}

	// get stdout IP
	http_paste_ip((uint32_t*)&stdout_server_addr.sin_addr.s_addr);

	// create stdout socket, optional
	std_sck = bsd_socket(2, 1, 6); // AF_INET, SOCK_STREAM, PROTO_TCP
	if(std_sck >= 0)
	{
		// connect to stdout server, optional
		if(bsd_connect(std_sck, (struct sockaddr*) &stdout_server_addr, sizeof(stdout_server_addr)) < 0)
		{
			bsd_close(std_sck);
			std_sck = -1; // invalidate
		}
	}

	// this exact sequence will redirect stdout to socket
	custom_stdout._write = stdout_debug;
	custom_stdout._flags = __SWR | __SNBF;
	custom_stdout._bf._base = (void*)1;
	stdout = &custom_stdout;
	stderr = &custom_stdout;

	// locate and hook webkit
	printf("searching for webkit ...\n");
	if(mem_install_hook(hook_func))
	{
		printf("- failed to locate webkit memories\n");
		bsd_close(std_sck);
		bsd_finalize();
		sm_finalize();
		return 1;
	}

	printf("- ready to exit\n");

	libtransistor_dont_finalize_bsd();
	libtransistor_set_close_browser();
	return 0;
}

