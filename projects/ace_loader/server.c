#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#include <libtransistor/ipc/nifm.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "server.h"
#include "memory.h"
#include "nro.h"
#include "http.h"

typedef struct
{
	void (*func)(char*);
	char *cmd;
	char *help;
} scmd_t;

static int sockets[2];
extern int std_sck;
extern struct sockaddr_in stdout_server_addr;

static int sck_bkup;
static int is_silent;

static uint8_t recv_buffer[RECV_BLOCKSIZE];

static_assert(sizeof(recv_buffer) >= sizeof(nro_header_t), "recv_buffer needs to be able to hold an entire NRO header");

void func_help(char*);
void func_echo(char*);
void func_stdout(char*);
void func_exec(char*);
void func_meminfo(char*);
void func_stats(char*);
void func_reboot(char*);
void func_args(char*);

static const scmd_t server_commands[] =
{
	{func_help, "help", NULL},
	{func_echo, "echo", NULL},
	{NULL, "exit", "exit loader"},
	{func_stdout, "stdout", "reconnect / disconnect / connect to stdout server"},
	{func_exec, "exec", "load and run NRO from HTTP server"},
	{func_meminfo, "meminfo", "print memory map using svcQueryMemory"},
	{func_stats, "stats", "print statistics"},
	{func_reboot, "reboot", "reboot the console"},
	{func_args, "args", "set name and arguments for directly uploaded NROs"},
};
#define NUM_CMDS (sizeof(server_commands) / sizeof(scmd_t))

static int cmd_compare(const char *t0, const char *t1)
{
	int i = 0;
	while(1)
	{
		if(*t1 == ' ')
		{
			if(*t0 != 0)
				return 0;
			else
				break;
		}
		if(*t0 != *t1)
			return 0;
		if(!*t0)
			break;
		t0++;
		t1++;
		i++;
	}
	return i;
}

int server_init()
{
	int sck;
	struct sockaddr_in server_addr =
	{
		.sin_family = AF_INET,
		.sin_port = htons(2991)
	};

	sck = bsd_socket(2, 1, 6); // AF_INET, SOCK_STREAM, PROTO_TCP
	printf("- server socket: %d, 0x%x, %d\n", sck, bsd_result, bsd_errno);
	if(sck < 0)
		return 1;

	if(bsd_bind(sck, (struct sockaddr *)&server_addr, sizeof(server_addr)))
	{
		printf("- bind failure\n");
		bsd_close(sck);
		return 2;
	}

	if(bsd_listen(sck, 1) < 0)
	{
		printf("- listen failure\n");
		bsd_close(sck);
		return 3;
	}

	sockets[0] = sck;
	sockets[1] = -1;
	return 0;
}

void server_loop()
{
	struct sockaddr_in client_addr;
	int ret;
	uint32_t idx;
	uint32_t ip;
	result_t r;

	void *nro_buf = NULL;
	size_t nro_size;

	bool is_command_mode;

	void *recv_ptr; // start of command/NRO buffer
	size_t recv_size; // size of received data
	size_t recv_remaining; // remaining space in command/NRO buffer
	
	printf("- starting push server ...\n");
	r = nifm_get_ip_address(&ip);
	if (r)
		printf("- Failed to get IP: nifm_get_ip_address returned %x\n", r);
	else
		printf("- IP is %u.%u.%u.%u\n", ip & 0xFF, (ip >> 8) & 0xFF, (ip >> 16) & 0xFF, (ip >> 24) & 0xFF);
	nifm_finalize();

	nro_arg_name("NRO"); // default args
	
	while(1)
	{
		if(sockets[1] == -1)
		{
			// server
			idx = sizeof(client_addr);
			ret = bsd_accept(sockets[0], (struct sockaddr *)&client_addr, &idx);
			if(ret < 0)
			{
				ret = bsd_errno;
				break;
			}
			sockets[1] = ret;
			printf("- client %i.%i.%i.%i:%i connected\n", client_addr.sin_addr.s_addr & 0xFF, (client_addr.sin_addr.s_addr >> 8) & 0xFF, (client_addr.sin_addr.s_addr >> 16) & 0xFF, client_addr.sin_addr.s_addr >> 24, ntohs(client_addr.sin_port));

			recv_ptr = recv_buffer;
			recv_size = 0;
			recv_remaining = sizeof(recv_buffer);
			is_command_mode = false;
			nro_buf = NULL;
		} else
		{
			// client
			ret = bsd_recv(sockets[1], recv_ptr + recv_size, recv_remaining, 0);
			if(ret < 0)
			{
				bsd_close(sockets[1]);
				sockets[1] = -1;
				printf("- client dropped (%d, 0x%x, %d)\n", ret, bsd_result, bsd_errno);
				continue;
			}
			if(ret == 0)
			{
				bsd_close(sockets[1]);
				sockets[1] = -1;
				printf("- client disconnected\n");
				// load and run NRO
				if(!is_command_mode) {
					uint64_t r = nro_execute(nro_buf, recv_size);
					printf("- NRO returned 0x%016lX\n", r);
					free_pages(nro_buf);
					nro_buf = NULL;
				}
				continue;
			}
			recv_size+= ret;
			recv_remaining-= ret;
			
			// is this an NRO?
			if(recv_size < sizeof(nro_header_t) || ((nro_header_t*) recv_ptr)->magic != NRO_MAGIC) {
				// it's not NRO, enable command mode
				is_command_mode = true;
			} else if(!nro_buf) {
				printf("- detected NRO\n");
				
				// this is an NRO, let's allocate some space for it
				is_command_mode = false; // just to make sure
				nro_size = ((nro_header_t*) recv_ptr)->nro_size;
				nro_buf = alloc_pages(nro_size + 0x1000, nro_size + 0x1000, NULL);
				
				if(nro_buf == NULL) {
					printf("- failed to allocate memory for NRO (size 0x%lx); dropping client\n", nro_size);
					bsd_close(sockets[1]);
					sockets[1] = -1;
					ap_dump_info();
					continue;
				}

				printf("- nro buffer %p\n", nro_buf);
				
				// use our newly allocated NRO buffer for receiving
				memcpy(nro_buf, recv_ptr, recv_size);
				recv_ptr = nro_buf;
				recv_remaining = (nro_size - recv_size) + 0x1000;
				continue;
			}
			
			if(is_command_mode)
			{
				// in command mode
				unsigned int i;
				char *command_start = recv_ptr;
				char *tmp = recv_ptr;

				// check for 'silent' commands
				if(tmp[0] == '!')
				{
					command_start++;
					is_silent = 1;
				} else
					is_silent = 0;
				// terminate string
				tmp[recv_size] = 0;
				// terminate at first newline
				while(*tmp)
				{
					if(*tmp == '\n' || *tmp == '\r')
					{
						*tmp = 0;
					}
					tmp++;
				}
				// find command
				for(i = 0; i < NUM_CMDS; i++)
				{
					int len = cmd_compare(server_commands[i].cmd, command_start);
					if(len)
					{
						// found command, execute
						sck_bkup = std_sck;

						// print info
						printf("- server command '%s'\n", server_commands[i].cmd);

						// redirect stdout to this client
						if(!is_silent)
							std_sck = sockets[1];

						if(!server_commands[i].func)
						{
							// exit
							if(!is_silent)
								printf("- exit loader\n");
							std_sck = sck_bkup;
							bsd_close(sockets[0]);
							bsd_close(sockets[1]);
							printf("- exit loader\n");
							return;
						}
						if(command_start[len] == ' ')
						{
							server_commands[i].func(recv_ptr + len + 1);
						} else
							server_commands[i].func(NULL);

						// restore stdout
						std_sck = sck_bkup;

						break;
					}
				}
				if(i == NUM_CMDS)
				{
					if(!is_silent)
					{
						sck_bkup = std_sck;
						std_sck = sockets[1];
						printf("- unknown command\n");
						std_sck = sck_bkup;
					}
					printf("- unknown command from client\n");
				}

				// compact buffer
				recv_size-= ((void*) tmp - recv_ptr);
				memmove(recv_ptr, tmp, recv_size);
				
				// let client know command has finished
				if(is_silent)
					bsd_send(sockets[1], "- done\n", 7, 0);
				// original NRO loading is disabled now
				continue;
			}

			// memory check
			if(recv_remaining <= 0)
			{
				bsd_close(sockets[1]);
				sockets[1] = -1;
				printf("- out of memory; client dropped\n");
				continue;
			}
		}
	}
	printf("- server error 0x%06X\n", ret);
}

//
// command functions

void func_help(char *par)
{
	unsigned int i;

	printf("server interface commands:\n");
	for(i = 0; i < NUM_CMDS; i++)
	{
		if(server_commands[i].help)
			printf("%s\t%s\n", server_commands[i].cmd, server_commands[i].help);
	}
}

void func_echo(char *par)
{
	if(!par)
	{
		printf("empty echo?\n");
		return;
	}

	printf("%s\n", par);
	std_sck = sck_bkup;
	printf("- echo '%s'\n", par);
	sck_bkup = std_sck;
	std_sck = sockets[1];
}

void func_stdout(char *par)
{
	if(!par)
	{
		printf("specify action; 'disconnect', 'reconnect' or 'connect'\n");
		return;
	}

	if(!strcmp(par, "disconnect"))
	{
		if(sck_bkup < 0)
			printf("- already disconnected\n");
		else
		{
			bsd_close(sck_bkup);
			sck_bkup = -1;
			printf("- stdout disconnected\n");
		}
		return;
	} else
	if(!strcmp(par, "reconnect"))
	{
		// disconnect first
		if(sck_bkup >= 0)
		{
			bsd_close(sck_bkup);
			sck_bkup = -1;
		}
		// reconnect to last one
	} else
	if(!strncmp(par, "connect ", 8))
	{
		unsigned int port, ip[4];
		// get new connection info
		if(sscanf(par+8, "%i.%i.%i.%i:%i", &ip[0], &ip[1], &ip[2], &ip[3], &port) != 5)
		{
			printf("- invalid connection\n");
			return;
		}
		stdout_server_addr.sin_port = htons(port);
		stdout_server_addr.sin_addr.s_addr = make_ip(ip[0],ip[1],ip[2],ip[3]);
		// disconnect now
		if(sck_bkup >= 0)
		{
			bsd_close(sck_bkup);
			sck_bkup = -1;
		}
	} else
	{
		printf("specify action; 'disconnect', 'reconnect' or 'connect ip:port'\n");
		return;
	}
	// make connection
	sck_bkup = bsd_socket(2, 1, 6); // AF_INET, SOCK_STREAM, PROTO_TCP
	if(sck_bkup >= 0)
	{
		if(bsd_connect(sck_bkup, (struct sockaddr*) &stdout_server_addr, sizeof(stdout_server_addr)) < 0)
		{
			bsd_close(sck_bkup);
			sck_bkup = -1; // invalidate
			printf("- stdout connection failed\n");
		} else
			printf("- connected to stdout server\n");
	} else
		printf("- socket creation failed\n");
}

void func_args(char *par)
{
	if(!par)
	{
		printf("current command line: ");
		nro_print_args();
		printf("\n");
		return;
	}
	
	char *arg = par;
	// parse name
	while(*par && *par != ' ')
		par++;
	if(*par)
	{
		*par = 0;
		par++;
		nro_arg_name(arg);
		// parse args
		while(*par)
		{
			// skip spaces
			while(*par && *par == ' ')
				par++;
			if(!*par)
				break;
			arg = par;
			// search for terminator
			while(*par && *par != ' ')
				par++;
			if(!*par)
			{
				// add arg and finish
				nro_add_arg(arg);
				break;
			}
			// add arg and go next
			*par = 0;
			par++;
			nro_add_arg(arg);
		}
	} else
		nro_arg_name(arg);
}

void func_exec(char *par)
{
	int ret;
	char *name = par;

	/*
	if(!par)
	{
		printf("specify server side path\n");
		return;
	}

	// parse name and arguments
	func_args(par);

	// load & run
	ret = http_get_file(name, heap_base, heap_size);
	if(ret > 0)
	{
		uint64_t r;
		printf("- starting NRO\n");
		r = nro_execute(heap_base, ret);
		printf("- NRO returned 0x%016lX\n", r);
	} else
	printf("- get NRO error %i\n", -ret);*/
}

void func_meminfo(char *par)
{
	ap_dump_info();
}

void func_stats(char *par)
{
	printf("ACE Loader stats:\n total NRO loads: %i\n currently loaded NROs: %i\n NRO unload errors: %i\n", nro_load_count, nro_loaded_count, nro_unload_fail);
}

void func_reboot(char *par)
{
	result_t r = bpc_reboot_system();
	printf("- failed to reboot system: 0x%06x\n", r); // in this case, even RESULT_OK is a failure because execution should've stopped
}
