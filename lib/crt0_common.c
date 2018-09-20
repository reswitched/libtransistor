#include<libtransistor/loader_config.h>
#include<libtransistor/util.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/tls.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/bsd.h>
#include<libtransistor/ipc/fs.h>
#include<libtransistor/ipc/fatal.h>
#include<libtransistor/ipc/twili.h>
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
#include<libtransistor/runtime_config.h>

#include<sys/socket.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<setjmp.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<stdnoreturn.h>

#include "default_squashfs_image.h"
#include "squashfs/squashfuse.h"

runconf_stdio_override_t _trn_runconf_stdio_override __attribute__((weak)) = _TRN_RUNCONF_STDIO_OVERRIDE_NONE;
const char *_trn_runconf_stdio_override_sockets_host __attribute__((weak)) = "ip.address.or.hostname";
const char *_trn_runconf_stdio_override_sockets_port __attribute__((weak)) = "2991";

runconf_heap_mode_t _trn_runconf_heap_mode __attribute__((weak)) = _TRN_RUNCONF_HEAP_MODE_DEFAULT;
void *_trn_runconf_heap_base __attribute__((weak)) = NULL;
size_t _trn_runconf_heap_size __attribute__((weak)) = 0;

int main(int argc, char **argv);

// from util.c
extern size_t log_length;
extern char log_buffer[0x20000];

// from environment.c
extern void *env_stack_top;

typedef struct {
	void (**init_array)(void);
	void (**fini_array)(void);

	ssize_t init_array_size;
	ssize_t fini_array_size;
} dyn_info_t;

typedef enum {
	NOT_EXITING = 0,
	NORMAL_EXIT = 1,
	DIRTY_EXIT = 2,
} exit_mode_t; // used for setjmp/longjmp

static jmp_buf exit_jmpbuf;
static int exit_value;
static uint8_t tls_backup[0x200];
static trn_thread_t main_thread;
static trn_inode_t root_inode;

static result_t setup_socket_stdio(int s_stdout, int s_stdin, int s_stderr);
static result_t setup_twili_stdio();
static result_t setup_usb_stdio();
static result_t setup_bss_stdio();
static result_t setup_fs();

void phal_init();

int _libtransistor_start(loader_config_entry_t *config, uint64_t thread_handle, void *aslr_base, void *stack_top) {
	result_t r;
	LIB_ASSERT_OK(fail, ld_relocate_module_basic(aslr_base));

	memcpy(tls_backup, get_tls(), 0x200);
	get_tls()->thread = NULL; // explicitly indicate that this thread has not yet been initialized
	
	dbg_printf("aslr base: %p", aslr_base);
	dbg_printf("config: %p", config);
	dbg_printf("stack top: %p", stack_top);

	env_stack_top = stack_top;

	// Initialize default behaviour for loader config
	lconfig_init_default(thread_handle);
	
	// parse loader config, if present
	if(config != NULL) {
		if(*((uint64_t*) config) == 0x007874635f656361) {
			dbg_printf("found libtransistor context-- please update ace_loader/pegaswitch!");

			// write log_buffer and log_size
			*((uint64_t*) (((uint8_t*) config) + 0x18)) = (uint64_t) log_buffer;
			*((uint64_t*) (((uint8_t*) config) + 0x20)) = (uint64_t) &log_length;

			r = LIBTRANSISTOR_ERR_LEGACY_CONTEXT;
			goto fail_tls;
		}
		
		dbg_printf("found loader config");
		
		LIB_ASSERT_OK(fail_tls, lconfig_parse(config));
		
		if(loader_config.main_thread == INVALID_HANDLE) {
			r = HOMEBREW_ABI_KEY_NOT_PRESENT(LCONFIG_KEY_MAIN_THREAD_HANDLE);
			goto fail_tls;
		}
	} else {
		dbg_printf("no loader config");
	}

	// set heap mode if loader_config overrides it
	if(_trn_runconf_heap_mode == _TRN_RUNCONF_HEAP_MODE_DEFAULT) {
		if(loader_config.heap_overridden) {
			_trn_runconf_heap_base = loader_config.heap_base;
			_trn_runconf_heap_size = loader_config.heap_size;
			_trn_runconf_heap_mode = _TRN_RUNCONF_HEAP_MODE_OVERRIDE;
		} else {
			_trn_runconf_heap_mode = _TRN_RUNCONF_HEAP_MODE_NORMAL;
		}
	}

	// prepare reent
	memset(get_tls(), 0, 0x200);
	memset(&main_thread, 0, sizeof(main_thread));
	main_thread.handle = loader_config.main_thread;
	main_thread.owns_stack = false;
	main_thread.arg = NULL;
	main_thread.pthread = NULL;
	_REENT_INIT_PTR(&main_thread.reent);
	get_tls()->thread = &main_thread;

	bool has_as = false;
	bool has_sm = false;
	bool has_fs = false;
	bool has_usb = false;
	bool has_twili = false;
	bool has_sockets = false;
	bool has_dbg_connection = false;
	module_t *root_module = NULL;
	
	exit_mode_t exit_mode = setjmp(exit_jmpbuf);
	if(exit_mode == NOT_EXITING) {
		LIB_ASSERT_OK(fail_tls, as_init());
		has_as = true;
		
		phal_init();

		/*
		  Automatically initialize sm, since 99% of applications are going to be using it
		  and if they don't explicitly initialize it, each ipc module will initialize it,
		  use it, then immediately finalize it.
		*/
		LIB_ASSERT_OK(fail_tls, sm_init());
		has_sm = true;
		
		if(_trn_runconf_stdio_override == _TRN_RUNCONF_STDIO_OVERRIDE_NONE) {
			if(loader_config.has_twili) {
				LIB_ASSERT_OK(fail_main, twili_init());
				has_twili = true;
				
				LIB_ASSERT_OK(fail_main, setup_twili_stdio());
			} else if(loader_config.has_stdio_sockets) {
				LIB_ASSERT_OK(fail_main, bsd_init_ex(true, loader_config.socket_service));
				has_sockets = true;

				LIB_ASSERT_OK(fail_main, setup_socket_stdio(
					              loader_config.socket_stdout,
					              loader_config.socket_stdin,
					              loader_config.socket_stderr));
			} else {
				LIB_ASSERT_OK(fail_main, setup_bss_stdio());
			}
		} else if(_trn_runconf_stdio_override == _TRN_RUNCONF_STDIO_OVERRIDE_USB_SERIAL) {
			LIB_ASSERT_OK(fail_main, setup_usb_stdio());
			has_usb = true;
		} else if(_trn_runconf_stdio_override == _TRN_RUNCONF_STDIO_OVERRIDE_SOCKETS) {
			LIB_ASSERT_OK(fail_main, bsd_init());
			has_sockets = true;
			
			int sock_fd;
			dbg_connect(_trn_runconf_stdio_override_sockets_host,
			            _trn_runconf_stdio_override_sockets_port, &sock_fd);
			dbg_printf("connected to overridden host -> %d", sock_fd);
			has_dbg_connection = true;
			
			dup2(sock_fd, STDOUT_FILENO);
			dup2(sock_fd, STDERR_FILENO);
			dup2(sock_fd, STDIN_FILENO);
			fd_close(sock_fd);
		} else if(_trn_runconf_stdio_override == _TRN_RUNCONF_STDIO_OVERRIDE_TWILI) {
			LIB_ASSERT_OK(fail_main, twili_init());
			has_twili = true;

			LIB_ASSERT_OK(fail_main, setup_twili_stdio());
		}

		LIB_ASSERT_OK(fail_main, setup_fs());
		has_fs = true;

		module_input_t root_input;
		root_input.name = "main";
		root_input.base = aslr_base;
		root_input.loader = NULL;
		root_input.is_global = true;
		root_input.has_run_basic_relocations = true;
		LIB_ASSERT_OK(fail_main, ld_add_module(root_input, &root_module));
		LIB_ASSERT_OK(fail_main, ld_process_modules());
		
		r = main(loader_config.argc, loader_config.argv);
		exit_mode = NORMAL_EXIT;
	} else if(exit_mode == NORMAL_EXIT || exit_mode == DIRTY_EXIT) {
		r = exit_value;
	} else {
		r = LIBTRANSISTOR_ERR_UNSPECIFIED;
	}

fail_main:
	if(exit_mode == NORMAL_EXIT ||
	   exit_mode == NOT_EXITING // when an assertion fails
		) {
		if(root_module != NULL) {
			ld_decref_module(root_module);
		}

		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		close(STDIN_FILENO);

		if(has_fs) {
			root_inode.ops->release(root_inode.data);
		}

		if(has_dbg_connection) {
			dbg_disconnect();
		}
		
		if(has_sockets) {
			bsd_finalize();
		}

		if(has_usb) {
			usb_serial_finalize();
		}
		
		if(has_twili) {
			twili_finalize();
		}
		
		if(has_sm) {
			sm_finalize();
		}
		
		if(has_as) {
			as_finalize();
		}
	}

fail_tls:
	memcpy(get_tls(), tls_backup, 0x200);
	if(!IS_NRO && r != 0) {
		fatal_init();
		fatal_transition_to_fatal_error(r, 0);
		while(1) {}
	}
fail:
	return r;
}

void _exit(int ret) {
	exit_value = ret;
	longjmp(exit_jmpbuf, NORMAL_EXIT);
}

noreturn void trn_dirty_exit(int ret) {
	exit_value = ret;
	longjmp(exit_jmpbuf, DIRTY_EXIT);
}

static result_t setup_twili_fd(result_t (*func)(twili_pipe_t *out), int fd) {
	result_t r;
	twili_pipe_t pipe;
	if((r = func(&pipe)) != RESULT_OK) {
		return r;
	}
	int pfd = twili_pipe_fd(&pipe);
	dup2(pfd, fd);
	close(pfd);
	return RESULT_OK;
}

static result_t setup_twili_stdio() {
	result_t r;
	LIB_ASSERT_OK(fail, setup_twili_fd(twili_open_stdout, STDOUT_FILENO));
	LIB_ASSERT_OK(fail_stdout, setup_twili_fd(twili_open_stderr, STDERR_FILENO));
	LIB_ASSERT_OK(fail_stderr, setup_twili_fd(twili_open_stdin, STDIN_FILENO));
	return RESULT_OK;
fail_stderr:
	close(STDERR_FILENO);
fail_stdout:
	close(STDOUT_FILENO);
fail:
	return r;
}


static result_t setup_stdio_socket(const char *name, int socket_fd, int target_fd) {
	int fd = socket_from_bsd(socket_fd);
	if (fd < 0) {
		dbg_printf("Error creating socket: %d", errno);
	} else {
		if (dup2(fd, target_fd) < 0) {
			dbg_printf("Error setting up %s: %d", name, errno);
		}
	}
	return RESULT_OK;
}

static result_t setup_socket_stdio(int s_stdout, int s_stdin, int s_stderr) {
	dbg_printf("using socklog stdio");
	setup_stdio_socket("stdout", loader_config.socket_stdout, STDOUT_FILENO);
	setup_stdio_socket("stdin",  loader_config.socket_stdin,  STDIN_FILENO);
	setup_stdio_socket("stderr", loader_config.socket_stderr, STDERR_FILENO);
	dbg_set_file(fd_file_get(loader_config.socket_stderr));
	return RESULT_OK;
}

static result_t setup_usb_stdio() {
	dbg_printf("using USB stdio");
	int usb_fd = usb_serial_open_fd();
	dbg_printf("got usb_fd -> %d", usb_fd);
	if(usb_fd < 0) {
		return 1;
	}
	dup2(usb_fd, STDOUT_FILENO);
	dup2(usb_fd, STDERR_FILENO);
	dup2(usb_fd, STDIN_FILENO);
	dbg_set_file(fd_file_get(usb_fd));
	fd_close(usb_fd);
	return RESULT_OK;
}

static result_t dbg_log_write(void *v, const void *ptr, size_t len, size_t *bytes_written) {
	log_string(ptr, len);
	*bytes_written = len;
	return RESULT_OK;
}

static result_t setup_bss_stdio() {
	static trn_file_ops_t fops = {
		.seek = NULL,
		.read = NULL,
		.write = dbg_log_write,
		.release = NULL,
	};
	int dbg_fd = fd_create_file(&fops, NULL);

	if(dbg_fd < 0) {
		dbg_printf("error making debug log fd");
	} else {
		dup2(dbg_fd, STDOUT_FILENO);
		dup2(dbg_fd, STDERR_FILENO);
	}
	fd_close(dbg_fd);
	return RESULT_OK;
}

// filesystem stuff
static blob_file sqfs_blob;
static sqfs fs;

static result_t setup_fs() {
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
	trn_inode_t squash_inode;
	if((r = trn_sqfs_open_root(&squash_inode, &fs)) != RESULT_OK) {
		printf("failed to open SquashFS root: %x\n", r);
		goto fail_mountfs;
	}

	if((r = trn_fs_mount("/squashfs", squash_inode)) != RESULT_OK) {
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
	trn_inode_t sdcard_inode;
	if((r = trn_fspfs_create(&sdcard_inode, sdcard_ifs)) != RESULT_OK) {
		printf("Failed to create fsp-srv vfs: %x\n", r);
		goto fail_sdcard_ifs;
	}
	if((r = trn_fs_mount("/sd", sdcard_inode)) != RESULT_OK) {
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
