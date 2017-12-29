#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/context.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/bsd.h>

#include<string.h>
#include<malloc.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define TRANSFER_MEM_SIZE 256*1024

result_t bsd_result;
int      bsd_errno;

static bool borrowing_bsd; // true if we're borrowing bsd object from our loader
static ipc_domain_t bsd_domain;
static ipc_object_t bsd_object;

static ipc_object_t iresolver_object;

static uint8_t __attribute__((aligned(0x1000))) transfer_buffer[TRANSFER_MEM_SIZE];
static transfer_memory_h transfer_mem;

static int bsd_initializations = 0;

result_t bsd_init() {
	result_t r;

	if(bsd_initializations++ > 0) {
		return RESULT_OK;
	}

	r = sm_init();
	if(r) {
		goto fail;
	}
	
	if(libtransistor_context.has_bsd) {
		borrowing_bsd = true;
		bsd_object = libtransistor_context.bsd_object;
	} else {
		borrowing_bsd = false;
		r = sm_get_service(&bsd_object, "bsd:u");
		if(r) {
			r = sm_get_service(&bsd_object, "bsd:s");
			if(r) {
				goto fail_sm;
			}
		}
  
		r = ipc_convert_to_domain(&bsd_object, &bsd_domain);
		if(r) {
			goto fail_bsd_domain;
		}
	}
  
	r = sm_get_service(&iresolver_object, "sfdnsres");
	if(r) {
		goto fail_bsd_domain;
	}

	if(!borrowing_bsd) {
		r = svcCreateTransferMemory(&transfer_mem, transfer_buffer, TRANSFER_MEM_SIZE, 0);
		if(r) {
			goto fail_iresolver;
		}

		struct {
			uint32_t fields[8];
			uint64_t pid_copy;
			uint64_t tmem_size;
		} raw;
		raw.fields[0] = 0x3;
		raw.fields[1] = 0x8000;
		raw.fields[2] = 0x10000;
		raw.fields[3] = 0x40000;
		raw.fields[4] = 0x40000;
		raw.fields[5] = 0x2400;
		raw.fields[6] = 0xA500;
		raw.fields[7] = 0x4;
		raw.pid_copy = 0;
		raw.tmem_size = TRANSFER_MEM_SIZE;
    
		ipc_request_t rq = ipc_default_request;
		rq.type = 4;
		rq.request_id = 0;
		rq.raw_data = (uint32_t*) &raw;
		rq.raw_data_size = sizeof(raw);
		rq.send_pid = true;
		rq.num_copy_handles = 1;
		rq.copy_handles = &transfer_mem;
    
		uint32_t response[1];
    
		ipc_response_fmt_t rs = ipc_default_response_fmt;
		rs.raw_data_size = sizeof(response);
		rs.raw_data = response;
    
		r = ipc_send(bsd_object, &rq, &rs);
    
		if(r) {
			goto fail_transfer_memory;
		}
    
		if(response[0]) {
			bsd_errno = response[0];
			r = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
			goto fail_transfer_memory;
		}
	}

	sm_finalize();
	
	return RESULT_OK;

fail_transfer_memory:
	svcCloseHandle(transfer_mem);
fail_iresolver:
	ipc_close(iresolver_object);
fail_bsd_domain:
	if(!borrowing_bsd) {
		ipc_close_domain(bsd_domain);
	}
fail_sm:
	sm_finalize();
fail:
	bsd_initializations--;
	return r;
}

ipc_object_t bsd_get_object() {
	return bsd_object;
}

// def tested via PS
// impl tested via Mephisto
int bsd_socket(int domain, int type, int protocol) {
	result_t r;

	uint32_t raw[] = {domain, type, protocol};
  
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	int32_t response[2]; // fd, errno
  
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;
  
	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}
  
	return response[0];
}

// def tested via PS
// impl untested
int bsd_recv(int socket, void *message, size_t length, int flags) {
	result_t r;

	uint32_t raw[] = {socket, flags};

	ipc_buffer_t buffer;
	buffer.addr = message;
	buffer.size = length;
	buffer.type = 0x22;

	ipc_buffer_t *buffers[] = {&buffer};

	ipc_request_t rq = ipc_default_request;
	rq.num_buffers = 1;
	rq.buffers = buffers;
	rq.request_id = 8;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	int32_t response[2]; // ret, errno

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;

	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}

	return response[0];
}

// def tested via PS
// impl tested via Mephisto
int bsd_send(int socket, const void *data, size_t length, int flags) {
	result_t r;

	uint32_t raw[] = {socket, flags};

	ipc_buffer_t buffer;
	buffer.addr = (void*) data;
	buffer.size = length;
	buffer.type = 0x21; // A+X

	ipc_buffer_t *buffers[] = {&buffer};
  
	ipc_request_t rq = ipc_default_request;
	rq.num_buffers = 1;
	rq.buffers = buffers;
	rq.request_id = 10;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	int32_t response[2]; // ret, errno

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;

	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}
  
	return response[0];
}

// def tested via PS
// impl untested
int bsd_sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len) {
	result_t r;

	uint32_t raw[] = {socket, flags};

	ipc_buffer_t message_buffer;
	message_buffer.addr = (void*) message;
	message_buffer.size = length;
	message_buffer.type = 0x21; // A+X

	ipc_buffer_t addr_buffer;
	addr_buffer.addr = (void*) dest_addr;
	addr_buffer.size = dest_len;
	addr_buffer.type = 0x21; // A+X

	ipc_buffer_t *buffers[] = {&message_buffer, &addr_buffer};

	ipc_request_t rq = ipc_default_request;
	rq.num_buffers = 2;
	rq.buffers = buffers;
	rq.request_id = 11;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	int32_t response[2]; // ret, errno

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;

	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}
  
	return response[0];
}

// def tested via PS
// impl untested
int bsd_accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
	result_t r;

	uint32_t raw[] = {socket};

	ipc_buffer_t addr_buffer;
	addr_buffer.addr = (void*) address;
	addr_buffer.size = *address_len;
	addr_buffer.type = 0x22;

	ipc_buffer_t *buffers[] = {&addr_buffer};
  
	ipc_request_t rq = ipc_default_request;
	rq.num_buffers = 1;
	rq.buffers = buffers;
	rq.request_id = 12;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	int32_t response[3]; // ret, errno, address_len
  
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;

	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}

	*address_len = response[2];
  
	return response[0];
}

// def tested via PS
// impl untested
int bsd_bind(int socket, const struct sockaddr *address, socklen_t address_len) {
	result_t r;

	uint32_t raw[] = {socket};

	ipc_buffer_t buffer;
	buffer.addr = (void*) address;
	buffer.size = address_len;
	buffer.type = 0x21; // A+X

	ipc_buffer_t *buffers[] = {&buffer};
  
	ipc_request_t rq = ipc_default_request;
	rq.num_buffers = 1;
	rq.buffers = buffers;
	rq.request_id = 13;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	int32_t response[2]; // ret, errno

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;

	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}
  
	return response[0];
}

// def tested via PS
// impl tested via Mephisto
int bsd_connect(int socket, const struct sockaddr *address, socklen_t address_len) {
	result_t r;

	uint32_t raw[] = {socket};

	ipc_buffer_t buffer;
	buffer.addr = (void*) address;
	buffer.size = address_len;
	buffer.type = 0x21; // A+X

	ipc_buffer_t *buffers[] = {&buffer};
  
	ipc_request_t rq = ipc_default_request;
	rq.num_buffers = 1;
	rq.buffers = buffers;
	rq.request_id = 14;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	uint32_t response[2]; // ret, errno

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = response;

	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] != 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}
  
	return response[0];
}

// def untested
int bsd_getsockname(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
	return 0;
}

// def tested via PS
int bsd_listen(int socket, int backlog) {
	result_t r;

	uint32_t raw[] = {socket, backlog};
  
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 18;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	int32_t response[2]; // ret, errno
  
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;
  
	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}
  
	return response[0];
}

// def untested
int bsd_setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len) {
	return 0;
}

// def untested
int bsd_shutdown(int socket, int how) {
	return 0;
}

// def untested
int bsd_select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout) {
	result_t r;

	uint64_t timeout_words[3];
	if(timeout != NULL) {
		timeout_words[0] = timeout->tv_sec;
		timeout_words[1] = timeout->tv_usec;
		timeout_words[2] = 0;
	} else {
		timeout_words[0] = 0;
		timeout_words[1] = 0;
		timeout_words[2] = 1;
	}

	uint32_t raw[7];
	raw[0] = nfds;
	memcpy(raw + 1, timeout_words, sizeof(timeout_words));
  
	ipc_buffer_t readfds_in = {
		.addr = readfds,
		.size = (readfds == NULL) ? 0 : sizeof(readfds),
		.type = 0x21
	};
	ipc_buffer_t writefds_in = {
		.addr = writefds,
		.size = (writefds == NULL) ? 0 : sizeof(writefds),
		.type = 0x21
	};
	ipc_buffer_t errorfds_in = {
		.addr = errorfds,
		.size = (errorfds == NULL) ? 0 : sizeof(errorfds),
		.type = 0x21
	};
	ipc_buffer_t readfds_out = {
		.addr = readfds,
		.size = (readfds == NULL) ? 0 : sizeof(readfds),
		.type = 0x22
	};
	ipc_buffer_t writefds_out = {
		.addr = writefds,
		.size = (writefds == NULL) ? 0 : sizeof(writefds),
		.type = 0x22
	};
	ipc_buffer_t errorfds_out = {
		.addr = errorfds,
		.size = (errorfds == NULL) ? 0 : sizeof(errorfds),
		.type = 0x22
	};
  
	ipc_buffer_t *buffers[] = {
		&readfds_in,
		&writefds_in,
		&errorfds_in,
		&readfds_out,
		&writefds_out,
		&errorfds_out
	};
    
	ipc_request_t rq = ipc_default_request;
	rq.num_buffers = 6;
	rq.buffers = buffers;
	rq.request_id = 5;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	int32_t response[2];

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;

	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}

	return response[0];
}

static int bsd_getaddrinfo_impl(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo *res, int limit) {
	result_t r;

	struct {
		uint8_t enable_nsd_resolve;
		uint8_t padding[3];
		uint32_t unknown;
		uint64_t pid;
	}  __attribute__((packed)) raw;

	raw.enable_nsd_resolve = 1;
	raw.unknown = 0;
	raw.pid = 0;

	uint8_t hints_packed[0x400];
	uint8_t response_packed[0x1000];

	memset(hints_packed, 0, sizeof(hints_packed));
	if(hints != NULL) {
		r = bsd_ai_pack(hints, hints_packed, sizeof(hints_packed));
		if(r) {
			bsd_result = r;
			return -1;
		}
	}
  
	ipc_buffer_t host_buf = {
		.addr = (void*) node,
		.size = (node == NULL) ? 0 : strlen(node)+1,
		.type = 5
	};
	ipc_buffer_t service_buf = {
		.addr = (void*) service,
		.size = (service == NULL) ? 0 : strlen(service)+1,
		.type = 5
	};
	ipc_buffer_t hints_buf = {
		.addr = hints_packed,
		.size = (hints == NULL) ? 0 : sizeof(hints_packed),
		.type = 5
	};
	ipc_buffer_t response_buf = {
		.addr = response_packed,
		.size = sizeof(response_packed),
		.type = 6
	};
  
	ipc_buffer_t *buffers[] = {
		&host_buf,
		&service_buf,
		&hints_buf,
		&response_buf
	};

	ipc_request_t rq = ipc_default_request;
	rq.num_buffers = 4;
	rq.buffers = buffers;
	rq.request_id = 6;
	rq.raw_data = (uint32_t*) &raw;
	rq.raw_data_size = sizeof(raw);
	rq.send_pid = true;
  
	int32_t response[3]; // ret, errno, response_size

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;

	r = ipc_send(iresolver_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}

	r = bsd_ai_unpack(res, response_packed, response[2], limit);
	if(r) {
		bsd_result = r;
		return -1;
	}
  
	return response[0];
}

int bsd_getaddrinfo_fixed(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo_fixed *res, int num_addrinfos) {
	for(int i = 0; i < num_addrinfos; i++) {
		res[i].ai.ai_addr = (struct sockaddr*) &(res[i].addr);
		res[i].ai.ai_canonname = res[i].canonname;
		res[i].ai.ai_next = (i+1) == num_addrinfos ? NULL : &(res[i + 1].ai);
	}
	return bsd_getaddrinfo_impl(node, service, hints, &res->ai, num_addrinfos);
}

int bsd_getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res) {
	struct addrinfo *ai;
	ai = malloc(sizeof(struct addrinfo));
	if(ai == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	memset(ai, 0, sizeof(struct addrinfo));
  
	result_t r;
	if((r = bsd_getaddrinfo_impl(node, service, hints, ai, -1)) != RESULT_OK) {
		free(ai);
		return r;
	}
	*res = ai;
	return r;
}

// def tested via PS
int bsd_close(int socket) {
	result_t r;

	uint32_t raw[] = {socket};
  
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 26;
	rq.raw_data = raw;
	rq.raw_data_size = sizeof(raw);

	int32_t response[2]; // ret, errno
  
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(response);
	rs.raw_data = (uint32_t*) response;
  
	r = ipc_send(bsd_object, &rq, &rs);
	if(r) {
		bsd_result = r;
		return -1;
	}

	if(response[0] < 0) {
		bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
		bsd_errno = response[1];
		return -1;
	}
  
	return response[0];
}

void bsd_finalize() {
	if(--bsd_initializations == 0) {
		ipc_close(iresolver_object);
		if(!borrowing_bsd) {
			svcCloseHandle(transfer_mem);
			ipc_close(bsd_object);
			ipc_close_domain(bsd_domain);
		}
		borrowing_bsd = false;
	}
}

result_t bsd_ai_pack(const struct addrinfo *ai, uint8_t *buf, size_t size) {
	struct {
		uint32_t magic;
		int32_t ai_flags;
		int32_t ai_family;
		int32_t ai_socktype;
		int32_t ai_protocol;
		int32_t ai_addrlen;
	}  __attribute__((packed)) ai_packed_header = {
		htonl(0xBEEFCAFE),
		htonl(ai->ai_flags),
		htonl(ai->ai_family),
		htonl(ai->ai_socktype),
		htonl(ai->ai_protocol),
		htonl(ai->ai_addrlen)
	};
  
	if(size < sizeof(ai_packed_header)) {
		return LIBTRANSISTOR_ERR_BSD_BUFFER_TOO_SMALL;
	}

	memcpy(buf, &ai_packed_header, sizeof(ai_packed_header));
	buf+= sizeof(ai_packed_header);
	size-= sizeof(ai_packed_header);

	if(size < (ai->ai_addrlen == 0 ? 4 : ai->ai_addrlen)) {
		return LIBTRANSISTOR_ERR_BSD_BUFFER_TOO_SMALL;
	}

	if(ai->ai_addrlen == 0) {
		*((uint32_t*) buf) = 0;
	} else {
		switch(ai->ai_family) {
		case AF_INET: {
			struct sockaddr_in *buf_as_sockaddr_in = (struct sockaddr_in*) buf;
			struct sockaddr_in *sockaddr = (struct sockaddr_in*) ai->ai_addr;
			buf_as_sockaddr_in->sin_len = 0;
			buf_as_sockaddr_in->sin_family = sockaddr->sin_family;
			buf_as_sockaddr_in->sin_port = htons(sockaddr->sin_port); // I think that this is erroneously byteswapped
			buf_as_sockaddr_in->sin_addr.s_addr = htonl(sockaddr->sin_addr.s_addr); // this too
			memset(&buf_as_sockaddr_in->sin_zero, 0, sizeof(buf_as_sockaddr_in->sin_zero));
			break;
		}
		case AF_INET6:
			// TODO
			return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
		default:
			memcpy(buf, ai->ai_addr, ai->ai_addrlen);
			break;
		}
	}
	buf+= ai->ai_addrlen;
	size-= ai->ai_addrlen == 0 ? 4 : ai->ai_addrlen;

	size_t canonlen = ai->ai_canonname == NULL ? 0 : strlen(ai->ai_canonname);
	if(size < canonlen + 1) {
		return LIBTRANSISTOR_ERR_BSD_BUFFER_TOO_SMALL;
	}

	memcpy(buf, ai->ai_canonname, canonlen);
	buf[canonlen] = 0;
	buf+= canonlen + 1;
	size-= canonlen + 1;

	if(ai->ai_next != NULL) {
		return bsd_ai_pack(ai->ai_next, buf, size);
	} else {
		if(size < 4) {
			return LIBTRANSISTOR_ERR_BSD_BUFFER_TOO_SMALL;
		}
		*((uint32_t*) buf) = 0;
		return 0;
	}
}

result_t bsd_ai_unpack(struct addrinfo *ai, const uint8_t *buf, size_t size, int limit) {
	if(limit == 0) { // -1 means no limit
		return RESULT_OK;
	}
  
	struct {
		uint32_t magic;
		int32_t ai_flags;
		int32_t ai_family;
		int32_t ai_socktype;
		int32_t ai_protocol;
		int32_t ai_addrlen;
	} __attribute__((packed)) ai_packed_header = {0, 0, 0, 0, 0, 0};

	result_t r;

	bool allocated_ai_addr = false;
	bool allocated_ai_canonname = false;
  
	if(size < sizeof(ai_packed_header)) {
		r = LIBTRANSISTOR_ERR_BSD_BUFFER_TOO_SMALL;
		goto bail;
	}
  
	memcpy(&ai_packed_header, buf, sizeof(ai_packed_header));
	buf+= sizeof(ai_packed_header);
	size-= sizeof(ai_packed_header);

	if(ntohl(ai_packed_header.magic) != 0xBEEFCAFE) {
		r = LIBTRANSISTOR_ERR_BSD_INVALID_MAGIC;
		goto bail;
	}
  
	ai->ai_flags = ntohl(ai_packed_header.ai_flags);
	ai->ai_family = ntohl(ai_packed_header.ai_family);
	ai->ai_socktype = ntohl(ai_packed_header.ai_socktype);
	ai->ai_protocol = ntohl(ai_packed_header.ai_protocol);
	ai->ai_addrlen = ntohl(ai_packed_header.ai_addrlen);
  
	if(ai->ai_addrlen == 0) {
		ai->ai_addr = NULL;
		buf+= 4;
		size-= 4;
	} else {
		if(ai->ai_addr == NULL) { // if this is already set, it's set to an existing buffer that we should use
			ai->ai_addr = malloc(ai->ai_addrlen);
			if(ai->ai_addr == NULL) {
				r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
				goto bail;
			}
			allocated_ai_addr = true;
		}
		switch(ai->ai_family) {
		case AF_INET: {
			struct sockaddr_in *buf_as_sockaddr_in = (struct sockaddr_in*) buf;
			struct sockaddr_in *sockaddr = (struct sockaddr_in*) ai->ai_addr;
			sockaddr->sin_len = 0;
			sockaddr->sin_family = buf_as_sockaddr_in->sin_family;
			sockaddr->sin_port = htons(buf_as_sockaddr_in->sin_port); // erroneous byte swapping
			sockaddr->sin_addr.s_addr = htonl(buf_as_sockaddr_in->sin_addr.s_addr); // again
			memset(&sockaddr->sin_zero, 0, sizeof(sockaddr->sin_zero));
			break;
		}
		case AF_INET6:
			// TODO
			return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
		default:
			memcpy(ai->ai_addr, buf, ai->ai_addrlen);
			break;
		}
		buf+= ai->ai_addrlen;
		size-= ai->ai_addrlen;
	}

	size_t canonlen = strlen((char*) buf);
	char *canonname;
	if(canonlen > 0) {
		if(ai->ai_canonname == NULL) {
			canonname = malloc(canonlen+1);
			if(canonname == NULL) {
				r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
				goto bail;
			}
			allocated_ai_canonname = true;
		} else {
			canonname = ai->ai_canonname;
		}
		memcpy(canonname, buf, canonlen+1);
	} else {
		canonname = NULL;
	}
	ai->ai_canonname = canonname;

	buf+= canonlen+1;
	size-= canonlen+1;

	if(*((uint32_t*) buf) == htonl(0xBEEFCAFE)) {
		bool allocated_ai_next = false;
		if(ai->ai_next == NULL) {
			struct addrinfo *next;
			next = malloc(sizeof(struct addrinfo));
			if(next == NULL) {
				return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
			}
			memset(next, 0, sizeof(struct addrinfo));
			ai->ai_next = next;
			allocated_ai_next = true;
		}
		r = bsd_ai_unpack(ai->ai_next, buf, size, limit-1);
		if(r) {
			if(allocated_ai_next) {
				free(ai->ai_next);
			}
			goto bail;
		}
	} else {
		ai->ai_next = NULL;
	}
  
	return 0;
  
bail:
	if(ai->ai_addr != NULL && allocated_ai_addr) {
		free(ai->ai_addr);
	}
	if(ai->ai_canonname != NULL && allocated_ai_canonname) {
		free(ai->ai_canonname);
	}
	return r;
}

void bsd_freeaddrinfo(struct addrinfo *res) {
	if(res->ai_next != NULL) {
		bsd_freeaddrinfo(res->ai_next);
	}
	if(res->ai_addr != NULL) {
		free(res->ai_addr);
	}
	if(res->ai_canonname != NULL) {
		free(res->ai_canonname);
	}
	free(res);
}
