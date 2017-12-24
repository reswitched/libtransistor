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

#include<libtransistor/context.h>
#include<libtransistor/fd.h>
#include<libtransistor/err.h>
#include<libtransistor/fs/fs.h>

void _exit(); // implemented in libtransistor crt0

int _close_r(struct _reent *reent, int file) {
	int res = fd_close(file);
	if (res < 0) {
		reent->_errno = -res;
		return -1;
	}
	return 0;
}

char *_environ[] = {NULL};

int _execve_r(struct _reent *reent, char *name, char **argv, char **env) {
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

int _link_r(struct _reent *reent, char *old, char *new) {
	reent->_errno = ENOSYS;
	return -1;
}

int _lseek_r(struct _reent *reent, int file, int pos, int whence) {
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

int _open_r(struct _reent *reent, const char *name, int flags, ...) {
	int fd;
	switch(trn_fs_open(&fd, name, flags)) {
	case RESULT_OK:
		return fd;
	case LIBTRANSISTOR_ERR_FS_NOT_A_DIRECTORY:
		reent->_errno = -ENOTDIR;
		break;
	case LIBTRANSISTOR_ERR_FS_NOT_FOUND:
		reent->_errno = -ENOENT;
		break;
	default:
		reent->_errno = ENOSYS;
		return -1;
	}
	return -1;
}

int _read_r(struct _reent *reent, int file, char *ptr, int len) {
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
	res = f->ops->read(f->data, ptr, len);
finalize:
	fd_file_put(f);
	if (res < 0) {
		reent->_errno = -res;
		return -1;
	}
	return res;
}

static size_t data_size = 0;

caddr_t _sbrk_r(struct _reent *reent, int incr) {
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

int _unlink_r(struct _reent *reent, char *name) {
	reent->_errno = ENOSYS;
	return -1;
}

int _wait_r(struct _reent *reent, int *status) {
	reent->_errno = ENOSYS;
	return -1;
}

int _write_r(struct _reent *reent, int file, char *ptr, int len) {
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
	res = f->ops->write(f->data, ptr, len);
finalize:
	fd_file_put(f);
	if (res < 0) {
		reent->_errno = -res;
		return -1;
	}
	return res;
}

int _gettimeofday_r(struct _reent *reent, struct timeval *__restrict p, void *__restrict z) {
	u64 time;
	result_t res;
	
	if (z != NULL) {
		reent->_errno = ENOSYS;
		return -1;
	}
	if (p == NULL) {
		reent->_errno = EINVAL;
		return -1;
	}
	sm_init();
	time_init();
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

char *realpath(const char *path, char *resolved_path) {
	char **resolved_path_var = &resolved_path;
	switch(trn_fs_realpath(path, resolved_path_var)) {
	case RESULT_OK:
		return resolved_path_var;
	case LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG:
		errno = ENAMETOOLONG;
		return NULL;
	case LIBTRANSISTOR_ERR_OUT_OF_MEMORY:
		errno = ENOMEM;
	}
	return NULL;
}

DIR *opendir(const char *name) {
	DIR *dir = malloc(sizeof(*dir));
	if(dir == NULL) {
		errno = ENOMEM;
		return NULL;
	}

	result_t r;
	switch(r = trn_fs_opendir(&dir->dir, name)) {
	case RESULT_OK:
		return dir;
	case LIBTRANSISTOR_ERR_FS_NOT_FOUND:
	case LIBTRANSISTOR_ERR_FS_INVALID_PATH:
		errno = ENOENT;
		break;
	case LIBTRANSISTOR_ERR_FS_NOT_A_DIRECTORY:
		errno = ENOTDIR;
		break;
	default:
		printf("unspec err: 0x%x\n", r);
		errno = EIO;
		break;
	}
	free(dir);
	return NULL;
}

struct dirent *readdir(DIR *dirp) {
	trn_dirent_t trn_dirent;
	
	switch(dirp->dir.ops->next(dirp->dir.data, &trn_dirent)) {
	case RESULT_OK:
		break;
	case LIBTRANSISTOR_ERR_FS_OUT_OF_DIR_ENTRIES:
		return NULL;
	default:
		errno = ENOSYS; // TODO: find a better errno
		return NULL;
	}

	dirp->ent.d_ino = 0;
	dirp->ent.d_namlen = trn_dirent.name_size;
	memcpy(dirp->ent.d_name, trn_dirent.name, 256);
	return &dirp->ent;
}

int closedir(DIR *dirp) {
	if(dirp->dir.ops->close != NULL) {
		dirp->dir.ops->close(dirp->dir.data);
	}
	return 0;
}

int mkdir(const char *path, mode_t mode) {
	errno = EROFS;
	return -1;
}
