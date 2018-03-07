#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/svc.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/bsd.h>
#include<libtransistor/ipc/fs/err.h>

#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

typedef struct {
	void *base;
	size_t size;
} memory_region_t;

static result_t get_region_from_info(memory_region_t *region, int base_id, int size_id) {
	result_t r;
	if((r = svcGetInfo(&region->base, base_id, 0xFFFF8001, 0)) != RESULT_OK) { return r; }
	if((r = svcGetInfo(&region->size, size_id, 0xFFFF8001, 0)) != RESULT_OK) { return r; }

	return RESULT_OK;
}

void *find_empty_memory_block(size_t len) {
	// find a suitable address for mapping the shared memory
	// TODO: Make sure the block is big enough to fit len.
	uint64_t addr;
	memory_info_t memory_info;
	result_t r;
	uint32_t page_info;

	memory_region_t disallowed_regions[3];
	if(get_region_from_info(&disallowed_regions[0], 2, 3) != RESULT_OK) { return NULL; } // MapRegion
	if(get_region_from_info(&disallowed_regions[1], 4, 5) != RESULT_OK) { return NULL; } // HeapRegion
	if(get_region_from_info(&disallowed_regions[2], 14, 15) != RESULT_OK) { return NULL; } // NewMapRegion

	// TODO: if we want to support 1.0.0, this will need a workaround
	memory_region_t address_space;
	if(get_region_from_info(&address_space, 12, 13) != RESULT_OK) { return NULL; } // AddressSpace
	
	do {
		uint64_t random = (uint64_t) rand() << 12;
		addr = (random % address_space.size) + address_space.base;

		bool is_overlapping = false;
		for(uint64_t i = 0; i < ARRAY_LENGTH(disallowed_regions); i++) {
			memory_region_t *r = &disallowed_regions[i];
			if((addr >= r->base && addr < (r->base + r->size)) ||
			   ((addr + len) >= r->base && (addr + len) < (r->base + r->size)) ||
			   (r->base >= addr && r->base < (addr + len)) ||
			   ((r->base + r->size) >= addr && (r->base + r->size) < (addr + len))) {
				is_overlapping = true;
				break;
			}
		}

		if(is_overlapping) {
			continue;
		}
		
		if((r = svcQueryMemory(&memory_info, &page_info, (void*) addr)) != RESULT_OK) {
			return NULL;
		}
	} while(memory_info.memory_type != 0 || memory_info.memory_attribute != 0 || memory_info.permission != 0 || (uint64_t) memory_info.base_addr + memory_info.size < addr + len);
	return (void*)addr;
}

uint64_t str2u64(const char *str) {
	char buf[8];
	int i = 0;
	for(; i < 8; i++) {
		if(str[i] == 0) { break; }
		buf[i] = str[i];
	}
	for(; i < 8; i++) {
		buf[i] = 0;
	}
	return *(uint64_t*) buf;
}

char nybble2hex(uint8_t nybble) {
	if(nybble < 10) {
		return '0' + nybble;
	} else {
		return 'a' + (nybble - 10);
	}
}

static int bsd_log = -1;
static bool dbg_owns_bsd_log = false;

void dbg_set_bsd_log(int fd) {
	dbg_disconnect();
	bsd_log = fd;
}

result_t dbg_connect(const char *host, const char *port) {
	result_t r;

	if((r = bsd_init()) != RESULT_OK) {
		goto fail;
	}

	struct addrinfo *ai = NULL;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int e = bsd_getaddrinfo(host, port, &hints, &ai);
	if(e) {
		r = bsd_result;
		goto fail;
	}

	if(ai == NULL) {
		goto fail;
	}

	bsd_log = bsd_socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	if(bsd_log < 0) {
		goto fail_ai;
	}

	if(bsd_connect(bsd_log, ai->ai_addr, ai->ai_addrlen) < 0) {
		goto fail_socket;
	}

	bsd_freeaddrinfo(ai);
	dbg_owns_bsd_log = true;
	
	return RESULT_OK;
	
fail_socket:
	bsd_close(bsd_log);
	bsd_log = -1;
fail_ai:
	bsd_freeaddrinfo(ai);
fail:
	return r;
}

__attribute__((destructor)) void dbg_disconnect() {
	if(dbg_owns_bsd_log && bsd_log >= 0) {
		bsd_close(bsd_log);
		dbg_owns_bsd_log = false;
	}
}

size_t log_length = 0;
char log_buffer[0x20000];

int log_string(const char *string, size_t len) {
	svcOutputDebugString((char*) string, len);
	size_t start = log_length;
	for(size_t i = 0; i < len && log_length < sizeof(log_buffer) - 2; i++) {
		if(string[i] == 0) { break; }
		log_buffer[log_length++] = string[i];
	}
	if (log_length < sizeof(log_buffer) - 1)
		log_buffer[log_length++] = '\n';
	if(bsd_log >= 0) {
		int olddebug = ipc_debug_flag;
		ipc_debug_flag = 0;
		bsd_send(bsd_log, log_buffer + start, log_length - start, 0);
		ipc_debug_flag = olddebug;
	}
	if (log_length < sizeof(log_buffer))
		log_buffer[log_length] = 0;
	return 4;
}

static void hexdump_impl(const void *rawbuf, size_t size, bool dbg) {
	const uint8_t *buf = rawbuf;
	char line[0x31 + 4 + 0x10 + 1];
	int i = 0;
	size_t total = 0;
	while(total < size) {
		i = 0;

		size_t linestart = total;

		// hexdump section
		while(total < linestart + 0x10) {
			if(total < size) {
				uint8_t byte = buf[total++];
				line[i++] = nybble2hex(byte >> 4);
				line[i++] = nybble2hex(byte & 15);
				line[i++] = ' ';
			} else {
				total++;
				line[i++] = ' ';
				line[i++] = ' ';
				line[i++] = ' ';
			}
			if(i == 3*8) { line[i++] = ' '; }
		}

		line[i++] = ' ';
		line[i++] = '|';
		line[i++] = ' ';
		line[i++] = ' ';

		total = linestart;
    
		while(total < linestart + 0x10) {
			if(total < size) {
				uint8_t ch = buf[total++];
				if(ch >= ' ' && ch < 0x7F) {
					line[i++] = ch;
				} else {
					line[i++] = '.';
				}
			} else {
				total++;
				line[i++] = ' ';
			}
		}

		line[i++] = 0;

		if(dbg) {
			log_string(line, i);
		} else {
			printf("%s\n", line);
		}
	}
}

void hexdump(const void *rawbuf, size_t size) {
	hexdump_impl(rawbuf, size, false);
}

void hexdump_dbg(const void *rawbuf, size_t size) {
	hexdump_impl(rawbuf, size, true);
}

void hexnum(int num) {
	char buf[16];
	buf[15] = 0;
	int i = 14;
	for(; num; i--, num>>= 4) {
		buf[i] = nybble2hex(num & 0xF);
	}
	buf[i--] = 'x';
	buf[i--] = '0';
	log_string(buf + i + 1, 16 - i);
}

#define STB_SPRINTF_IMPLEMENTATION
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdouble-promotion"
#pragma clang diagnostic ignored "-Wconditional-uninitialized"
#include<libtransistor/stb_sprintf.h>
#pragma clang diagnostic pop

#include<stdarg.h>

int dbg_printf(char const *fmt, ...) {
	va_list vl;
	char buf[512];
	int ret;
	va_start(vl, fmt);
	ret = dbg_vsnprintf(buf, 511, fmt, vl);
	log_string(buf, ret+1);
	va_end(vl);
	return ret;
}

int trn_result_to_errno(result_t r) {
	switch (r) {
		case RESULT_OK:
			return 0;
		case FSPSRV_ERR_NOT_FOUND:
		case LIBTRANSISTOR_ERR_FS_NOT_FOUND:
		case LIBTRANSISTOR_ERR_FS_INVALID_PATH:
			return ENOENT;
		case FSPSRV_ERR_EXISTS:
		case LIBTRANSISTOR_ERR_FS_PATH_EXISTS:
			return EEXIST;
		case LIBTRANSISTOR_ERR_FS_NOT_A_DIRECTORY:
			return ENOTDIR;
		case LIBTRANSISTOR_ERR_OUT_OF_MEMORY:
			return ENOMEM;
		case LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG:
			return ENAMETOOLONG;
		case FSPSRV_ERR_DIRECTORY_NOT_EMPTY:
			return ENOTEMPTY;
		case LIBTRANSISTOR_ERR_FS_READ_ONLY:
			return EROFS;
		case LIBTRANSISTOR_ERR_FS_ACCESS_DENIED:
			return EACCES;
		default:
			// Make the debugger's life easy: print his error before turning it
			// into a useless code...
			printf("UNSUPPORTED ERROR: %x\n", r);
			return ENOSYS;
	}
}
