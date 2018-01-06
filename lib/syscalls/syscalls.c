/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <reent.h>

#include <libtransistor/tls.h>
#include<libtransistor/context.h>
#include<libtransistor/fd.h>
#include<libtransistor/ipc/time.h>

void _exit(); // implemented in libtransistor crt0

struct _reent *__getreent() {
	struct tls *tls = get_tls();
	if (tls == NULL || tls->ctx == NULL)
		return NULL;
	else
		return &tls->ctx->reent;
}

int _close_r(struct _reent *reent, int file) {
	int res = fd_close(file);
	if (res < 0) {
		reent->_errno = -res;
		return -1;
	}
	return 0;
}

char *_environ[] = {NULL};

int _execve_r(struct _reent *reent, const char *name, char *const *argv, char *const *env) {
	reent->_errno = ENOSYS;
	return -1;
}

int _fork_r(struct _reent *reent) {
	reent->_errno = ENOSYS;
	return -1;
}

int _fstat_r(struct _reent *reent, int file, struct stat *st) {
	reent->_errno = ENOSYS;
	return -1;
}

int _getpid_r(struct _reent *reent) {
	reent->_errno = ENOSYS;
	return -1;
}

int _isatty_r(struct _reent *reent, int file) {
	reent->_errno = ENOSYS;
	return -1;
}

int _kill_r(struct _reent *reent, int pid, int sig) {
	reent->_errno = ENOSYS;
	return -1;
}

int _link_r(struct _reent *reent, const char *old, const char *new) {
	reent->_errno = ENOSYS;
	return -1;
}

off_t _lseek_r(struct _reent *reent, int file, off_t pos, int whence) {
	ssize_t res = 0;

	struct file *f = fd_file_get(file);
	if (f == NULL) {
		reent->_errno = EBADF;
		return -1;
	}

	if (f->ops->llseek == NULL) {
		res = -ENOSYS;
		goto finalize;
	}
	res = f->ops->llseek(f->data, pos, whence);
finalize:
	fd_file_put(f);
	if (res < 0) {
		reent->_errno = -res;
		return -1;
	}
	return res;
}

int _open_r(struct _reent *reent, const char *name, int flags, int mode) {
	reent->_errno = ENOSYS;
	return -1;
}

ssize_t _read_r(struct _reent *reent, int file, void *ptr, size_t len) {
	ssize_t res = 0;

	struct file *f = fd_file_get(file);
	if (f == NULL) {
		reent->_errno = EBADF;
		return -1;
	}

	if (f->ops->read == NULL) {
		res = -ENOSYS;
		goto finalize;
	}
	res = f->ops->read(f->data, (char*)ptr, len);
finalize:
	fd_file_put(f);
	if (res < 0) {
		reent->_errno = -res;
		return -1;
	}
	return res;
}

static size_t data_size = 0;

void *_sbrk_r(struct _reent *reent, ptrdiff_t incr) {
	if(data_size + incr > libtransistor_context.mem_size) {
		reent->_errno = ENOMEM;
		return (void*) -1;
	}

	void *addr = libtransistor_context.mem_base + data_size;
	data_size+= incr;
	
	return addr;
}

int _stat_r(struct _reent *reent, const char *file, struct stat *st) {
	reent->_errno = ENOSYS;
	return -1;
}

clock_t _times_r(struct _reent *reent, struct tms *buf) {
	reent->_errno = ENOSYS;
	return (clock_t) -1;
}

int _unlink_r(struct _reent *reent, const char *name) {
	reent->_errno = ENOSYS;
	return -1;
}

int _wait_r(struct _reent *reent, int *status) {
	reent->_errno = ENOSYS;
	return -1;
}

ssize_t _write_r(struct _reent *reent, int file, const void *ptr, size_t len) {
	ssize_t res = 0;

	struct file *f = fd_file_get(file);
	if (f == NULL) {
		reent->_errno = EBADF;
		return -1;
	}

	if (f->ops->write == NULL) {
		res = -ENOSYS;
		goto finalize;
	}
	res = f->ops->write(f->data, (char*)ptr, len);
finalize:
	fd_file_put(f);
	if (res < 0) {
		reent->_errno = -res;
		return -1;
	}
	return res;
}

int _gettimeofday_r(struct _reent *reent, struct timeval *__restrict p, void *__restrict z) {
	uint64_t time;
	result_t res;
	
	if (z != NULL) {
		reent->_errno = ENOSYS;
		return -1;
	}
	if (p == NULL) {
		reent->_errno = EINVAL;
		return -1;
	}
	
	static bool time_initialized = false;
	if(!time_initialized) {
		time_init();
		time_initialized = true;
		atexit(time_finalize);
	}
	
	if ((res = time_get_current_time(&time)) != RESULT_OK) {
		reent->_errno = -EINVAL;
		return -1;
	}
	p->tv_sec = time;
	// No usec support on here :(.
	p->tv_usec = 0;
	return 0;
}

long sysconf(int name) {
	switch(name) {
	case _SC_PAGESIZE:
		return 0x1000;
	}
	errno = ENOSYS;
	return 01;
}
