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
#include <dirent.h>
#include <malloc.h>
#include <string.h>
#include <reent.h>

#include<libtransistor/loader_config.h>
#include<libtransistor/err.h>
#include<libtransistor/svc.h>
#include<libtransistor/tls.h>
#include<libtransistor/fd.h>
#include<libtransistor/ipc/time.h>
#include<libtransistor/fd.h>
#include<libtransistor/svc.h>
#include<libtransistor/fs/fs.h>
#include<libtransistor/util.h>

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
	int fd;
	result_t r;

	if ((r = trn_fs_open(&fd, name, flags)) != RESULT_OK) {
		reent->_errno = trn_result_to_errno(r);
		return -1;
	}
	return fd;
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
static size_t actual_data_size = 0; // used if not overriding heap
static void *heap_addr = NULL;
#define HEAP_SIZE_INCREMENT 0x2000000

void *_sbrk_r(struct _reent *reent, ptrdiff_t incr) {
	void *addr;
	if(loader_config.heap_overridden) {
		if(data_size + incr > loader_config.heap_size) {
			reent->_errno = ENOMEM;
			return (void*) -1;
		}
		
		addr = loader_config.heap_base + data_size;
		data_size+= incr;
		return addr;
	} else {
		if(data_size + incr > actual_data_size || heap_addr == NULL) {
			ptrdiff_t corrected_incr = data_size + incr - actual_data_size;
			ptrdiff_t rounded_incr = (corrected_incr + HEAP_SIZE_INCREMENT - 1) & ~(HEAP_SIZE_INCREMENT-1);
			result_t r = svcSetHeapSize(&heap_addr, actual_data_size + rounded_incr);
			if(r != RESULT_OK) {
				reent->_errno = ENOMEM;
				return (void*) -1;
			}
			actual_data_size+= rounded_incr;
		}
		
		addr = heap_addr + data_size;
		data_size+= incr;
		return addr;
	}
}

int _stat_r(struct _reent *reent, const char *file, struct stat *st) {
	result_t r;

	if ((r = trn_fs_stat(file, st)) != RESULT_OK) {
		reent->_errno = trn_result_to_errno(r);
		return -1;
	}
	return 0;
}

clock_t _times_r(struct _reent *reent, struct tms *buf) {
	reent->_errno = ENOSYS;
	return (clock_t) -1;
}

int _unlink_r(struct _reent *reent, const char *name) {
	result_t r;

	if ((r = trn_fs_unlink(name)) != RESULT_OK) {
		reent->_errno = trn_result_to_errno(r);
		return -1;
	}
	return 0;
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
	
	if ((res = time_system_clock_get_current_time(time_system_clock_user, &time)) != RESULT_OK) {
		reent->_errno = -EINVAL;
		return -1;
	}
	p->tv_sec = time;
	// No usec support on here :(.
	p->tv_usec = 0;
	return 0;
}

int rmdir(const char *path) {
	result_t r;

	if ((r = trn_fs_rmdir(path)) != RESULT_OK) {
		errno = trn_result_to_errno(r);
		return -1;
	}
	return 0;
}

long sysconf(int name) {
	switch(name) {
	case _SC_PAGESIZE:
		return 0x1000;
	}
	errno = ENOSYS;
	return -1;
}

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp) {
	svcSleepThread(rqtp->tv_nsec + (rqtp->tv_sec * 1000000000));
	return 0;
}

int posix_memalign (void **memptr, size_t alignment, size_t size) {
	void *mem;
	
	if (alignment % sizeof(void *) != 0 || (alignment & (alignment - 1)) != 0) {
    return EINVAL;
	}

	mem = memalign(alignment, size);
	
	if (mem != NULL) {
		*memptr = mem;
		return 0;
	}
	
	return ENOMEM;
}

int _rename_r(struct _reent *reent, const char *old, const char *new) {
	// TODO: implement this
	reent->_errno = EROFS;
	return 01;
}

ssize_t readlink(const char *restrict path, char *restrict buf, size_t bufsize) {
	errno = ENOSYS;
	return -1;
}

char *realpath(const char *path, char *resolved_path) {
	char **resolved_path_var = &resolved_path;
	result_t r;

	if ((r = trn_fs_realpath(path, resolved_path_var)) != RESULT_OK) {
		errno = trn_result_to_errno(r);
		return NULL;
	}
	return *resolved_path_var;
}

DIR *opendir(const char *name) {
	DIR *dir = malloc(sizeof(*dir));
	if(dir == NULL) {
		errno = ENOMEM;
		return NULL;
	}

	result_t r;
	if ((r = trn_fs_opendir(&dir->dir, name)) != RESULT_OK) {
		errno = trn_result_to_errno(r);
		free(dir);
		return NULL;
	}
	return dir;
}

struct dirent *readdir(DIR *dirp) {
	trn_dirent_t trn_dirent;
	result_t r;

	switch((r = dirp->dir.ops->next(dirp->dir.data, &trn_dirent))) {
	case RESULT_OK:
		break;
	case LIBTRANSISTOR_ERR_FS_OUT_OF_DIR_ENTRIES:
		return NULL;
	default:
		errno = trn_result_to_errno(r);
		return NULL;
	}

	dirp->ent.d_ino = 0;
	dirp->ent.d_namlen = trn_dirent.name_size;
	memcpy(dirp->ent.d_name, trn_dirent.name, 256);
	if (trn_dirent.name_size >= 256)
		dirp->ent.d_name[255] = '\0';
	else
		dirp->ent.d_name[trn_dirent.name_size] = '\0';

	return &dirp->ent;
}

int closedir(DIR *dirp) {
	if(dirp->dir.ops->close != NULL) {
		dirp->dir.ops->close(dirp->dir.data);
	}
	return 0;
}

int mkdir(const char *path, mode_t mode) {
	result_t r;
	if ((r = trn_fs_mkdir(path)) != RESULT_OK) {
		errno = trn_result_to_errno(r);
		return -1;
	}
	return 0;
}

int rename(const char *oldpath, const char *newpath) {
	result_t r;
	if ((r = trn_fs_rename(oldpath, newpath)) != RESULT_OK) {
		errno = trn_result_to_errno(r);
		return -1;
	}
	return 0;
}
