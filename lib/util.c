#include<libtransistor/util.h>

#include<libtransistor/types.h>
#include<libtransistor/mutex.h>
#include<libtransistor/err.h>
#include<libtransistor/svc.h>
#include<libtransistor/fd.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/bsd.h>
#include<libtransistor/ipc/fs/err.h>

#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

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

static trn_recursive_mutex_t debug_file_mutex = TRN_RECURSIVE_MUTEX_STATIC_INITIALIZER;
static trn_file_t *debug_file GUARDED_BY(debug_file_mutex) = NULL;

void dbg_set_file(trn_file_t *file) {
	trn_recursive_mutex_lock(&debug_file_mutex);
	dbg_printf("redirecting dbgout to %p\n", file);
	fd_file_put(debug_file);
	debug_file = file;
	trn_recursive_mutex_unlock(&debug_file_mutex);
}

result_t dbg_connect(const char *host, const char *port, int *fd_out) {
	result_t r;

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
		r = bsd_result;
		goto fail;
	}

	int fd = bsd_socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	if(fd < 0) {
		r = bsd_result;
		goto fail_ai;
	}

	if(bsd_connect(fd, ai->ai_addr, ai->ai_addrlen) < 0) {
		r = bsd_result;
		goto fail_socket;
	}

	bsd_freeaddrinfo(ai);

	int std_fd = socket_from_bsd(fd);
	dbg_set_file(fd_file_get(std_fd));
	*fd_out = std_fd;
	
	return RESULT_OK;
	
fail_socket:
	bsd_close(fd);
fail_ai:
	bsd_freeaddrinfo(ai);
fail:
	return r;
}

__attribute__((destructor)) void dbg_disconnect() {
	trn_recursive_mutex_lock(&debug_file_mutex);
	fd_file_put(debug_file);
	debug_file = NULL;
	trn_recursive_mutex_unlock(&debug_file_mutex);
}

static trn_mutex_t log_mutex = TRN_MUTEX_STATIC_INITIALIZER;
size_t log_length GUARDED_BY(log_mutex) = 0;
char log_buffer[0x20000] GUARDED_BY(log_mutex);

int log_string(const char *string, size_t len) {
	svcOutputDebugString((char*) string, len);

	trn_mutex_lock(&log_mutex);
	size_t start = log_length;
	for(size_t i = 0; i < len && log_length < sizeof(log_buffer) - 2; i++) {
		if(string[i] == 0) { break; }
		log_buffer[log_length++] = string[i];
	}
	if(log_length < sizeof(log_buffer) - 1) {
		log_buffer[log_length++] = '\n';
	}
	trn_recursive_mutex_lock(&debug_file_mutex);
	if(debug_file != NULL) {
		ipc_debug_level_t olddebug = ipc_debug_level;
		ipc_debug_level = IPC_DEBUG_LEVEL_NONE;
		size_t bytes_written;
		debug_file->ops->write(debug_file->data, log_buffer + start, log_length - start, &bytes_written);
		ipc_debug_level = olddebug;
	}
	trn_recursive_mutex_unlock(&debug_file_mutex);
	if (log_length < sizeof(log_buffer))
		log_buffer[log_length] = 0;
	trn_mutex_unlock(&log_mutex);
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
	trn_result_description_t d;
	trn_lookup_result(r, &d);
	return d.closest_errno;
}
