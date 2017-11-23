#include <libtransistor/nx.h>
#include <stdio.h>

#include <ssp/ssp.h>

#define make_ip(a,b,c,d)	((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))

static FILE customout;
static int sck;

const struct sockaddr_in server_addr =
{
	.sin_family = AF_INET,
	.sin_port = htons(2991),
	.sin_addr = {
		.s_addr = make_ip(192,168,121,131)
	}
};

int stdout_debug(struct _reent *reent, void *v, const char *ptr, int len)
{
	bsd_send(sck, ptr, len, 0);
	return len;
}

void explode_stack()
{
	char buffer[10];
	
	for (int i = 0; i <= 10; i++)
	{
		// When compiled with stack protector support, this line
		//   will print something to the effect of:
		//
		//   *** stack smashing detected ***: <unknown> terminated
		//   Aborted (core dumped)
		//
		//   when i == 10, because 10 is an out of bounds write.
		//   This will throw a SIGABRT, retruning code 134.

		buffer[i] = (char)i;
	}
}

int main()
{
	svcSleepThread(100000000);

	if(sm_init() != RESULT_OK)
		return 1;

	if(bsd_init() != RESULT_OK)
	{
		sm_finalize();
		return 1;
	}

	sck = bsd_socket(2, 1, 6); // AF_INET, SOCK_STREAM, PROTO_TCP
	if(sck < 0)
	{
		bsd_finalize();
		sm_finalize();
		return 1;
	}

	if(bsd_connect(sck, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
	{
		bsd_finalize();
		sm_finalize();
		return 1;
	}

	// this exact sequence will redirect stdout to socket
	printf("_"); // init stdout
	customout._write = stdout_debug;
	customout._flags = __SWR | __SNBF;
	customout._bf._base = (void*)1;
	stdout = &customout;
	stderr = &customout;

	explode_stack();

	return 0;
}
