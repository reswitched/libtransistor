#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#include <libtransistor/loader_config.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "memory.h"
#include "http.h"
#include "server.h"
#include "nro.h"
#include "common_setup.h"

FILE custom_stdout;
int std_sck;

struct sockaddr_in stdout_server_addr =
{
	.sin_family = AF_INET,
	.sin_port = htons(STDOUT_PORT),
};

int common_init(int argc, char **argv) {
	const char *hostname;

	int ret = 0;
	
	if(argc == 0)
		hostname = "a.b"; // PegaSwitch will respond to any DNS request
	else
		hostname = argv[0]; // use provided hostname

	ipc_debug_level = IPC_DEBUG_LEVEL_NONE;

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
		} else {
			// redirect stdout and stderr
			int fd = socket_from_bsd(std_sck);
			if(fd < 0) {
				printf("error creating fd\n");
			} else {
				dup2(fd, STDOUT_FILENO);
				dup2(fd, STDERR_FILENO);
				dbg_set_bsd_log(std_sck);
			}
		}
	}

	return ret;
}

result_t common_begin_server() {
	int ret = 0;
	void *ptr;
	
	// initialize RO
	ret = ro_init();
	if(ret)
	{
		printf("- ldr:ro initialization error 0x%06X\n", ret);
		return ret;
	}

	ret = bpc_init();
	if(ret)
	{
		printf("- bpc initialization error 0x%06x\n", ret);
		return ret;
	}

	ret = nifm_init();
	if(ret)
	{
		printf("- nifm initialization error 0x%06x\n", ret);
		return ret;
	}

	// release sm; it's not needed anymore
	sm_finalize();

	/*
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
			return 0;
			}*/

	// start 'push' server
	if(!server_init())
		server_loop();
	return 0;
}
