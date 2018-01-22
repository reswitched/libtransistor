#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/bsd.h>

#include<stdlib.h>
#include<stdio.h>

void *find_empty_memory_block(size_t len) {
	// find a suitable address for mapping the shared memory
	// TODO: Make sure the block is big enough to fit len.
	uint64_t addr;
	memory_info_t memory_info;
	result_t r;
	uint32_t page_info;
	do {
		addr = (uint64_t) rand() << 32 | rand();
		addr += 0x80000000;
		addr &= 0x0000007FFFFFF000;
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

void dbg_set_bsd_log(int fd) {
	bsd_log = fd;
}

size_t log_length = 0;
char log_buffer[0x20000];

int log_string(const char *string, size_t len) {
	svcOutputDebugString((char*) string, len);
	size_t start = log_length;
	for(size_t i = 0; i < len; i++) {
		if(string[i] == 0) { break; }
		log_buffer[log_length++] = string[i];
	}
	log_buffer[log_length++] = '\n';
	if(bsd_log >= 0) {
		int olddebug = ipc_debug_flag;
		ipc_debug_flag = 0;
		bsd_send(bsd_log, log_buffer + start, log_length - start, 0);
		ipc_debug_flag = olddebug;
	}
	log_buffer[log_length] = 0;
	return 4;
}

void hexdump(const void *rawbuf, size_t size) {
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

		printf("%s\n", line);
	}
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
