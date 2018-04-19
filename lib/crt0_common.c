#include<libtransistor/loader_config.h>
#include<libtransistor/util.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/tls.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/bsd.h>
#include<libtransistor/ipc/fs.h>
#include<libtransistor/fs/blobfd.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/fs/squashfs.h>
#include<libtransistor/fs/mountfs.h>
#include<libtransistor/fs/fspfs.h>
#include<libtransistor/fs/fs.h>
#include<libtransistor/fd.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/address_space.h>
#include<libtransistor/usb_serial.h>
#include<libtransistor/ld/ld.h>

#include<sys/socket.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<setjmp.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<rthread.h>
#include<stdnoreturn.h>

#include "default_squashfs_image.h"
#include "squashfs/squashfuse.h"

const enum {
	STDIO_OVERRIDE_NONE,
	STDIO_OVERRIDE_USB_SERIAL,
	STDIO_OVERRIDE_SOCKETS,
} STDIO_OVERRIDE = STDIO_OVERRIDE_NONE;

const char *STDIO_OVERRIDE_SOCKETS_HOST = "ip.address.or.hostname";
const char *STDIO_OVERRIDE_SOCKETS_PORT = "2991";

int main(int argc, char **argv);

// from util.c
extern size_t log_length;
extern char log_buffer[0x20000];

typedef struct {
	void (**init_array)(void);
	void (**fini_array)(void);

	ssize_t init_array_size;
	ssize_t fini_array_size;
} dyn_info_t;

static result_t dbg_log_write(void *v, const void *ptr, size_t len, size_t *bytes_written) {
	log_string(ptr, len);
	*bytes_written = len;
	return RESULT_OK;
}

// filesystem stuff
static blob_file sqfs_blob;
static sqfs fs;
static trn_inode_t root_inode;
static trn_inode_t squash_inode;
static trn_inode_t sdcard_inode;

bool setup_fs() {
	size_t sqfs_size = ((uint8_t*) &_libtransistor_squashfs_image_end) - ((uint8_t*) &_libtransistor_squashfs_image); // TODO: not this
	int sqfs_img_fd = blobfd_create(&sqfs_blob, &_libtransistor_squashfs_image, sqfs_size);
	sqfs_err err = SQFS_OK;
	ifilesystem_t sdcard_ifs;

	err = sqfs_init(&fs, sqfs_img_fd, 0);
	if(err != SQFS_OK) {
		printf("failed to open SquashFS image: %x\n", err);
		goto fail_sqfs_image_fd;
	}

	result_t r;
	// Setup mountfs
	if((r = trn_mountfs_create(&root_inode)) != RESULT_OK) {
		printf("Failed to create mountfs: %x\n", r);
		goto fail_sqfs;
	}
	if((r = trn_fs_set_root(&root_inode)) != RESULT_OK) {
		printf("Failed to set mountfs as root: %x\n", r);
		goto fail_mountfs;
	}

	// Mounting squashfs to /squash
	if((r = trn_sqfs_open_root(&squash_inode, &fs)) != RESULT_OK) {
		printf("failed to open SquashFS root: %x\n", r);
		goto fail_mountfs;
	}

	if((r = trn_fs_mount("/squashfs", &squash_inode)) != RESULT_OK) {
		printf("failed to mount SquashFS: %x\n", r);
		goto fail_trn_sqfs;
	}

	// Mount sdcardfs to /sd
	if((r = fsp_srv_init(0)) != RESULT_OK) {
		printf("Failed to open connection to fsp-srv: %x\n", r);
		goto fail_mounted_sqfs;
	}
	if((r = fsp_srv_mount_sd_card(&sdcard_ifs)) != RESULT_OK) {
		printf("Failed to mount sdcard on fsp-srv: %x\n", r);
		goto fail_fsp_srv;
	}
	if((r = trn_fspfs_create(&sdcard_inode, sdcard_ifs)) != RESULT_OK) {
		printf("Failed to create fsp-srv vfs: %x\n", r);
		goto fail_sdcard_ifs;
	}
	if((r = trn_fs_mount("/sd", &sdcard_inode)) != RESULT_OK) {
		printf("failed to mount sdcard: %x\n", r);
		goto fail_fspfs;
	}

	return false;

fail_fspfs:
	sdcard_inode.ops->release(sdcard_inode.data);
fail_sdcard_ifs:
	ipc_close(sdcard_ifs);
fail_fsp_srv:
	fsp_srv_finalize();
fail_mounted_sqfs:
	return false; // these are not fatal errors
	
fail_trn_sqfs:
	squash_inode.ops->release(squash_inode.data);
fail_mountfs:
	root_inode.ops->release(root_inode.data);
fail_sqfs:
	sqfs_destroy(&fs);
fail_sqfs_image_fd:
	close(sqfs_img_fd);
	return true;
}

typedef enum {
	NOT_EXITING = 0,
	NORMAL_EXIT = 1,
	DIRTY_EXIT = 2,
} exit_mode_t; // used for setjmp/longjmp

static jmp_buf exit_jmpbuf;
static int exit_value;

static uint8_t tls_backup[0x200];

static trn_thread_t main_thread;

static void setup_stdio_socket(const char *name, int socket_fd, int target_fd);
static int make_dbg_log_fd();

extern void _cleanup_mapped_heap();

int _libtransistor_start(loader_config_entry_t *config, uint64_t thread_handle, void *aslr_base) {
	int ret;
	if((ret = ld_relocate_module_basic(aslr_base)) != RESULT_OK) {
		return ret;
	}

	memcpy(tls_backup, get_tls(), 0x200);
	get_tls()->thread = NULL; // explicitly indicate that this thread has not yet been initialized
	
	dbg_printf("aslr base: %p", aslr_base);
	dbg_printf("config: %p", config);

	// Initialize default behaviour for loader config
	lconfig_init_default(thread_handle);
	
	// parse loader config, if present
	if(config != NULL) {
		if(*((uint64_t*) config) == 0x007874635f656361) {
			dbg_printf("found libtransistor context-- please update ace_loader/pegaswitch!");

			// write log_buffer and log_size
			*((uint64_t*) (((uint8_t*) config) + 0x18)) = log_buffer;
			*((uint64_t*) (((uint8_t*) config) + 0x20)) = &log_length;
			
			return LIBTRANSISTOR_ERR_LEGACY_CONTEXT;
		}
		
		dbg_printf("found loader config");
		
		ret = lconfig_parse(config);
		if(ret != RESULT_OK) {
			return ret;
		}
		
		if(loader_config.main_thread == INVALID_HANDLE) {
			return HOMEBREW_ABI_KEY_NOT_PRESENT(LCONFIG_KEY_MAIN_THREAD_HANDLE);
		}
	} else {
		dbg_printf("no loader config");
		// Temporary fix to run this in Mephisto.
		loader_config.main_thread = 0xde00;
	}

	memset(get_tls(), 0, 0x200);
	main_thread.handle = loader_config.main_thread;
	main_thread.owns_stack = false;
	main_thread.arg = NULL;
	main_thread.pthread = NULL;
	_REENT_INIT_PTR(&main_thread.reent);
	get_tls()->thread = &main_thread;
	
	bool initialized_fs = false;

	module_t *root_module = NULL;
	
	exit_mode_t exit_mode = setjmp(exit_jmpbuf);
	if(exit_mode == NOT_EXITING) {
		ret = as_init();
		if(ret != RESULT_OK) {
			return ret;
		}
		
		dbg_printf("init alloc_pages");
		ret = ap_init();
		if(ret != RESULT_OK) {
			return ret;
		}
		
		dbg_printf("init threads");
		phal_tid tid = { .id = loader_config.main_thread, .stack = NULL };
		_rthread_internal_init(tid);

		/*
		  Automatically initialize sm, since 99% of applications are going to be using it
		  and if they don't explicitly initialize it, each ipc module will initialize it,
		  use it, then immediately finalize it.
		*/
		if((ret = sm_init()) != RESULT_OK) {
			dbg_printf("failed to initialize sm: 0x%x", ret);
			goto restore_tls;
		}
		
		if(STDIO_OVERRIDE == STDIO_OVERRIDE_NONE) {
			if(loader_config.has_stdio_sockets) {
				if((ret = bsd_init_ex(true, loader_config.socket_service)) != RESULT_OK) {
					sm_finalize();
					goto restore_tls;
				}
				
				dbg_printf("using socklog stdio");
				setup_stdio_socket("stdout", loader_config.socket_stdout, STDOUT_FILENO);
				setup_stdio_socket("stdin",  loader_config.socket_stdin,  STDIN_FILENO);
				setup_stdio_socket("stderr", loader_config.socket_stderr, STDERR_FILENO);
				dbg_set_file(fd_file_get(loader_config.socket_stderr));
			} else {
				dbg_printf("using bsslog stdout");
				int dbg_fd = make_dbg_log_fd();
				if(dbg_fd < 0) {
					dbg_printf("error making debug log fd");
				} else {
					dup2(dbg_fd, STDOUT_FILENO);
					dup2(dbg_fd, STDERR_FILENO);
				}
				fd_close(dbg_fd);
			}
		} else if(STDIO_OVERRIDE == STDIO_OVERRIDE_USB_SERIAL) {
			dbg_printf("using USB stdio");
			int usb_fd = usb_serial_open_fd();
			dbg_printf("got usb_fd -> %d", usb_fd);
			if(usb_fd < 0) {
				sm_finalize();
				goto restore_tls;
			}
			dup2(usb_fd, STDOUT_FILENO);
			dup2(usb_fd, STDERR_FILENO);
			dup2(usb_fd, STDIN_FILENO);
			dbg_set_file(fd_file_get(usb_fd));
			fd_close(usb_fd);
		} else if(STDIO_OVERRIDE == STDIO_OVERRIDE_SOCKETS) {
			int sock_fd;
			int e;
			dbg_connect(STDIO_OVERRIDE_SOCKETS_HOST, STDIO_OVERRIDE_SOCKETS_PORT, &sock_fd);
			dbg_printf("connected to overridden host -> %d", sock_fd);
			e = dup2(sock_fd, STDOUT_FILENO);
			e = dup2(sock_fd, STDERR_FILENO);
			e = dup2(sock_fd, STDIN_FILENO);
			fd_close(sock_fd);
		}

		dbg_printf("set up stdout");
		
		if(setup_fs()) {
			ret = -14;
			goto fail_bsd;
		}
		initialized_fs = true;

		module_input_t root_input;
		root_input.name = "main";
		root_input.base = aslr_base;
		root_input.type = MODULE_TYPE_MAIN;
		if((ret = ld_add_module(root_input, &root_module)) != RESULT_OK) {
			root_inode.ops->release(root_inode.data);
			dbg_disconnect();
			goto fail_bsd;
		}
		if((ret = ld_process_modules()) != RESULT_OK) {
			ld_decref_module(root_module); // error handling?
			root_module = NULL;
			root_inode.ops->release(root_inode.data);
			dbg_disconnect();
			goto fail_bsd;
		}
		
		ret = main(loader_config.argc, loader_config.argv);
		exit_mode = NORMAL_EXIT;
	} else if(exit_mode == NORMAL_EXIT || exit_mode == DIRTY_EXIT) {
		ret = exit_value;
	} else {
		ret = LIBTRANSISTOR_ERR_UNSPECIFIED;
	}

	if(exit_mode == NORMAL_EXIT) {
		if(initialized_fs) {
			// Clean up FS
			root_inode.ops->release(root_inode.data);
		}

		dbg_disconnect();
		
		if(root_module != NULL) {
			ld_decref_module(root_module); // error handling?
			root_module = NULL;
		}

		dbg_printf("cleaning up mapped heap");
		_cleanup_mapped_heap();
		dbg_printf("cleaned heap");

		as_finalize();
	}

fail_bsd:
	/*
	  at this point, bsd and sm have already been destructed, but just in case we
	  ever change the destruction logic...
	 */
	if(loader_config.has_stdio_sockets) {
		bsd_finalize();
	}
	sm_finalize();

restore_tls:
	memcpy(get_tls(), tls_backup, 0x200);
	return ret;
}

void _exit(int ret) {
	exit_value = ret;
	longjmp(exit_jmpbuf, NORMAL_EXIT);
}

noreturn void trn_dirty_exit(int ret) {
	exit_value = ret;
	longjmp(exit_jmpbuf, DIRTY_EXIT);
}

static void setup_stdio_socket(const char *name, int socket_fd, int target_fd) {
	int fd = socket_from_bsd(socket_fd);
	if (fd < 0) {
		dbg_printf("Error creating socket: %d", errno);
	} else {
		if (dup2(fd, target_fd) < 0) {
			dbg_printf("Error setting up %s: %d", name, errno);
		}
	}
}

static int make_dbg_log_fd() {
	static trn_file_ops_t fops = {
		.write = dbg_log_write
	};
	return fd_create_file(&fops, NULL);
}
