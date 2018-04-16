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
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/fs/fs.h>
#include<libtransistor/util.h>
#include<libtransistor/mutex.h>

void _exit(); // implemented in libtransistor crt0

struct _reent *__getreent() {
	return &trn_get_thread()->reent;
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
	off_t res = 0;

	trn_file_t *f = fd_file_get(file);
	if (f == NULL) {
		reent->_errno = EBADF;
		return -1;
	}

	if (f->ops->seek == NULL) {
		res = -ENOSYS;
		goto finalize;
	}

	result_t r = f->ops->seek(f->data, pos, whence, &res);
	
finalize:
	fd_file_put(f);
	
	if(r != RESULT_OK) {
		reent->_errno = trn_result_to_errno(r);
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
	size_t res = 0;

	trn_file_t *f = fd_file_get(file);
	if (f == NULL) {
		reent->_errno = EBADF;
		return -1;
	}

	if (f->ops->read == NULL) {
		res = -ENOSYS;
		goto finalize;
	}
	
	result_t r = f->ops->read(f->data, (char*)ptr, len, &res);
	
finalize:
	fd_file_put(f);
	
	if(r != RESULT_OK) {
		reent->_errno = trn_result_to_errno(r);
		return -1;
	}
	
	return res;
}

static void *map_addr = NULL;
static ssize_t map_size = 0;
static ssize_t map_limit = 0;
static size_t reported_size = 0;

typedef struct {
	void *dst;
	void *src;
	size_t size;
} map_entry_t;

static map_entry_t map_entries[512];
static int num_map_entries = 0;

void *_sbrk_r(struct _reent *reent, ptrdiff_t incr) {
	result_t r;
	if(map_addr == NULL) {
		if((r = svcGetInfo((uint64_t*) &map_addr, 14, 0xFFFF8001, 0)) != RESULT_OK) {
			reent->_errno = ENOMEM;
			return (void*) -1;
		}
		if((r = svcGetInfo(&map_limit, 15, 0xFFFF8001, 0)) != RESULT_OK) {
			reent->_errno = ENOMEM;
			return (void*) -1;
		}
		dbg_printf("map addr: %p, limit: 0x%zx\n", map_addr, map_limit);

		memory_info_t minfo;
		uint32_t pinfo;

		// the loader may have already mapped pages at the start of this region
		while(1) {
			if((r = svcQueryMemory(&minfo, &pinfo, map_addr)) != RESULT_OK) {
				reent->_errno = ENOMEM;
				return (void*) -1;
			}
			if(minfo.memory_type != 0) {
				map_limit-= (minfo.base_addr + minfo.size) - (map_addr);
				if(map_limit < 0 || minfo.base_addr + minfo.size < map_addr) {
					reent->_errno = ENOMEM;
					return (void*) -1;
				}
				map_addr = minfo.base_addr + minfo.size;
			} else {
				break;
			}
		}
	}

	if(reported_size + incr > map_size) {
		ptrdiff_t corrected_incr = reported_size + incr - map_size;
		ptrdiff_t rounded_incr = ((corrected_incr + 0xfff) >> 12) << 12;
	
		if(map_size + rounded_incr > map_limit) {
			dbg_printf("hit mapping limit");
			reent->_errno = ENOMEM;
			return (void*) -1;
		}

		while(rounded_incr > 0) {
			if(num_map_entries >= ARRAY_LENGTH(map_entries)) {
				reent->_errno = ENOMEM;
				return (void*) -1;
			}

			size_t src_size;
			void *src = alloc_pages(0x1000, rounded_incr, &src_size);
			r = svcMapMemory(map_addr + map_size, src, src_size);
			if(r != RESULT_OK) {
				dbg_printf("map memory failed: 0x%x", r);
				reent->_errno = ENOMEM;
				return (void*) -1;
			}
			map_entry_t entry = {
				.dst = map_addr + map_size,
				.src = src,
				.size = src_size
			};
			map_entries[num_map_entries++] = entry;
			map_size+= src_size;
			rounded_incr-= src_size;
		}
	}

	void *addr = map_addr + reported_size;
	reported_size+= incr;
	return addr;
}

void _cleanup_mapped_heap() {
	result_t r;
	
	for(int i = 0; i < num_map_entries; i++) {
		map_entry_t e = map_entries[i];
		if((r = svcUnmapMemory(e.dst, e.src, e.size)) != RESULT_OK) {
			dbg_printf("failed to unmap %p -> %p, 0x%x\n", e.src, e.dst, e.size);
		} else {
			free_pages(e.src);
		}
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
	size_t res = 0;

	trn_file_t *f = fd_file_get(file);
	if (f == NULL) {
		reent->_errno = EBADF;
		return -1;
	}

	if (f->ops->write == NULL) {
		res = -ENOSYS;
		goto finalize;
	}
	
	result_t r = f->ops->write(f->data, (char*)ptr, len, &res);
	
finalize:
	fd_file_put(f);
	
	if(r != RESULT_OK) {
		reent->_errno = trn_result_to_errno(r);
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
	return -1;
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

static trn_recursive_mutex_t malloc_mutex = TRN_RECURSIVE_MUTEX_STATIC_INITIALIZER;

void __malloc_lock(struct _reent *reent) {
	trn_recursive_mutex_lock(&malloc_mutex);
}

void __malloc_unlock(struct _reent *reent) {
	trn_recursive_mutex_unlock(&malloc_mutex);
}
