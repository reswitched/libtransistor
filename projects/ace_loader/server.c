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
	if(sck < 0)
		return 1;

	if(bsd_bind(sck, (struct sockaddr *)&server_addr, sizeof(server_addr)))
	{
		bsd_close(sck);
		return 2;
	}

	if(bsd_listen(sck, 1) < 0)
	{
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
	void *ptr = NULL;
	uint64_t size = 0;
	uint32_t ip;
	result_t r;

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
			// reset pointer
			ptr = heap_base;
			size = heap_size;
		} else
		{
			// client
			ret = bsd_recv(sockets[1], ptr, RECV_BLOCKSIZE, 0);
			if(ret < 0)
			{
				bsd_close(sockets[1]);
				sockets[1] = -1;
				printf("- client dropped\n");
				continue;
			}
			if(ret == 0)
			{
				bsd_close(sockets[1]);
				sockets[1] = -1;
				printf("- client disconnected\n");
				// load and run NRO
				if(size != heap_size && size != 0xFFFFFFFF)
				{
					size = nro_execute(heap_base, (int)(ptr - heap_base));
					printf("- NRO returned 0x%016lX\n", size);
				}
				continue;
			}
			// check for command
			if(size == heap_size)
			{
				if(ret < 0x14 || *(uint32_t*)(ptr+0x10) != NRO_MAGIC)
					// it's not NRO, enable command mode
					size = 0xFFFFFFFF;
			}
			if(size == 0xFFFFFFFF)
			{
				// in commad mode
				unsigned int i;
				uint8_t *tmp = ptr;

				// check for 'silent' commands
				if(tmp[0] == '!')
				{
					ptr++;
					is_silent = 1;
				} else
					is_silent = 0;
				// terminate string
				tmp[ret] = 0;
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
					int len = cmd_compare(server_commands[i].cmd, ptr);
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
						if(*(uint8_t*)(ptr+len) == ' ')
						{
							server_commands[i].func(ptr + len + 1);
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
				// restore pointer - might be changed
				ptr = heap_base;
				// let client know command has finished
				if(is_silent)
					bsd_send(sockets[1], "- done\n", 7, 0);
				// original NRO loading is disabled now
				continue;
			}
			// move pinter
			size -= ret;
			ptr += ret;
			// memory check
			if(size < RECV_BLOCKSIZE)
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
		printf("- get NRO error %i\n", -ret);
}

void func_meminfo(char *par)
{
	mem_info();
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
