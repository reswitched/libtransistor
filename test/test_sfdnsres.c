#include<libtransistor/nx.h>

#include<sys/socket.h>
#include<string.h>
#include<stdio.h>

void dumpsockaddrin(struct sockaddr_in *sin) {
	printf("sin_family: %d\n", sin->sin_family);
	printf("sin_port: %d\n", ntohs(sin->sin_port));
	uint32_t addr = sin->sin_addr.s_addr;
	uint8_t *bytes = (uint8_t*) &addr;
	printf("sin_addr: %d.%d.%d.%d\n", bytes[0], bytes[1], bytes[2], bytes[3]);
}

void dumpaddrinfo(struct addrinfo *ai) {
	printf("ai_flags: %d\n", ai->ai_flags);
	printf("ai_family: %d\n", ai->ai_family);
	printf("ai_socktype: %d\n", ai->ai_socktype);
	printf("ai_protocol: %d\n", ai->ai_protocol);
	printf("ai_addrlen: %d\n", ai->ai_addrlen);
	if(ai->ai_family == AF_INET) {
		dumpsockaddrin((struct sockaddr_in*) ai->ai_addr);
	}
	if(ai->ai_canonname) {
		printf("ai_canonname: \"%s\"\n", ai->ai_canonname);
	} else {
		printf("ai_canonname: NULL\n");
	}
	if(ai->ai_next) {
		printf("ai_next:\n");
		dumpaddrinfo(ai->ai_next);
	}
}

int main() {
	svcSleepThread(100000000);
  
	result_t r;
	if((r = sm_init()) != RESULT_OK) {
		printf("failed to init sm: 0x%x\n", r);
		return 1;
	}

	if((r = bsd_init()) != RESULT_OK) {
		printf("failed to init bsd: 0x%x, %d\n", r, bsd_errno);
		goto err_only_sm;
	}

	struct addrinfo *ai = NULL;

	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
  
	int e = bsd_getaddrinfo("conntest.nintendowifi.net", "6767", &hints, &ai);
	if(e) {
		printf("failed to getaddrinfo: %d, 0x%x\n", e, bsd_result);
		goto err;
	}

	if(ai == NULL) {
		printf("addrinfo is null?\n");
		goto err;
	}
  
	dumpaddrinfo(ai);
  
	bsd_freeaddrinfo(ai);

	struct addrinfo_fixed ai_fixed[2];
	e = bsd_getaddrinfo_fixed("conntest.nintendowifi.net", "6767", &hints, ai_fixed, 2);
	if(e) {
		printf("failed to getaddrinfo: %d, 0x%x\n", e, bsd_result);
		goto err;
	}

	ai = &ai_fixed[0].ai;
  
	if(ai->ai_addr != (struct sockaddr*) &ai_fixed[0].addr) {
		printf("unexpected ai->ai_addr\n");
		goto err;
	}
	if(ai->ai_canonname != NULL && ai->ai_canonname != ai_fixed[0].canonname) {
		printf("unexpected ai->ai_canonname\n");
		goto err;
	}
	if(ai->ai_next != NULL && ai->ai_next != &ai_fixed[1].ai) {
		printf("unexpected ai->ai_next\n");
		goto err;
	}
  
	dumpaddrinfo(ai);
  
	bsd_finalize();
	sm_finalize();
	return 0;
  
err:
	bsd_finalize();
err_only_sm:
	sm_finalize();
	return 1;  
}
