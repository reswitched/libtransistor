#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
#include "http.h"
#include "memory.h"

static FILE http_stdout;
static int sck; // HTTP socket

static const char http_get_template[] = "GET /files/%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: ACE loader\r\nAccept-Encoding: none\r\nConnection: close\r\n\r\n";
char http_hostname[128];

static struct sockaddr_in server_addr =
{
	.sin_family = AF_INET,
	.sin_port = htons(80)
};

static int stdout_http(struct _reent *reent, void *v, const char *ptr, int len)
{
	bsd_send(sck, ptr, len, 0);
	return len;
}

static int parse_header(char *buf, int len, int *offset, int *got)
{
	char *ptr = buf;
	char *pptr = buf;
	int ret;
	int state = 0;
	int content_length = 0;

	while(len)
	{
		// get some bytes
		ret = bsd_recv(sck, ptr, len, 0);
		if(ret <= 0)
			return -1;
		ptr += ret;
		// parse line(s)
		while(1)
		{
			char *tptr = pptr;
			char *eptr = pptr + ret;
			// get line end
			while(tptr < eptr)
			{
				if(*tptr == '\n')
				{
					if(tptr - pptr <= 1)
					{
						// empty line, header ending
						if(state)
						{
							*offset = (int)((tptr + 1) - buf);
							*got = (int)((ptr - buf) - *offset);
							return content_length;
						} else
							return -2;
					}
					// got one line, parse it
					if(state)
					{
						if(!strncmp(pptr, "Content-Length:", 15))
							sscanf(pptr + 15, "%d", &content_length);
					} else
					{
						int v1, v2, res;
						// HTTP response
						state = 1;
						if(sscanf(pptr, "HTTP/%d.%d %d", &v1, &v2, &res) != 3 || !res)
							return -1;
						if(res != 200)
							return -res;
					}
					// go next
					pptr = tptr + 1;
					break;
				}
				tptr++;
			}
			if(tptr == pptr)
				// no more lines left
				break;
		}
		// go next
		len -= ret;
	}
	
	return -1;
}

int http_init(const char *hostname)
{
	int ret;
	struct addrinfo_fixed aif;
	struct sockaddr_in *sin;
	struct addrinfo hints =
	{
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM
	};

	// get IP
	ret = bsd_getaddrinfo_fixed(hostname, "6767", &hints, &aif, 1);
	if(ret)
		return ret;

	if(aif.ai.ai_family != AF_INET)
		return 2;
	sin = (struct sockaddr_in*)&aif.addr;
	server_addr.sin_addr.s_addr = sin->sin_addr.s_addr;

//	printf("- host '%s' IP is %i.%i.%i.%i\n", hostname, server_addr.sin_addr.s_addr & 0xFF, (server_addr.sin_addr.s_addr >> 8) & 0xFF, (server_addr.sin_addr.s_addr >> 16) & 0xFF, server_addr.sin_addr.s_addr >> 24);

	// copy hostname
	strncpy(http_hostname, hostname, sizeof(http_hostname)-1);

	// prepare HTTP stdout
	http_stdout._write = stdout_http;
	http_stdout._flags = __SWR | __SNBF;
	http_stdout._bf._base = (void*)1;

	return 0;
}

void http_paste_ip(uint32_t *target)
{
	*target = server_addr.sin_addr.s_addr;
}

int http_get_file(const char *path, void *buff, uint64_t maxsize)
{
	char temp[1024];
	int ret, offs, got;
	void *ptr;
	int size;

	sck = bsd_socket(2, 1, 6); // AF_INET, SOCK_STREAM, PROTO_TCP
	if(sck < 0)
		return -1;

	if(bsd_connect(sck, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
	{
		bsd_close(sck);
		return -2;
	}

	// make a request
	fprintf(&http_stdout, http_get_template, path, http_hostname);

	// get an answer
	ret = parse_header(temp, sizeof(temp), &offs, &got);
	// load it now
	if(ret > 0)
	{
		printf("- HTTP file size: %iB\n", ret);
		if(ret > maxsize)
		{
			bsd_close(sck);
			printf("- file is too big\n");
			return -3;
		}
		ptr = buff;
		size = ret;
		if(got)
		{
			memcpy(ptr, temp + offs, got);
			ptr += got;
			size -= got;
		}
		while(size)
		{
			got = bsd_recv(sck, ptr, size, 0);
			if(got <= 0)
			{
				bsd_close(sck);
				printf("- read error\n");
				return -4;
			}
			size -= got;
			ptr += got;
		}
		printf("- file loaded\n");
	}

	bsd_close(sck);
	return ret;
}

