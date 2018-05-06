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

typedef struct {
	uint32_t magic, dynamic_off, bss_start_off, bss_end_off;
	uint32_t unwind_start_off, unwind_end_off, module_object_off;
} module_header_t;

typedef struct {
	int64_t d_tag;
	union {
		uint64_t d_val;
		void *d_ptr;
	};
} Elf64_Dyn;

typedef struct {
	uint64_t r_offset;
	uint32_t r_reloc_type;
	uint32_t r_symbol;
	uint64_t r_addend;
} Elf64_Rela;

static_assert(sizeof(Elf64_Rela) == 0x18, "Elf64_Rela size should be 0x18");

typedef struct {
	void (**init_array)(void);
	void (**fini_array)(void);

	ssize_t init_array_size;
	ssize_t fini_array_size;
} dyn_info_t;

const bool RELOCATION_DEBUG = false; // run under Mephisto with --relocate

static result_t relocate(uint8_t *aslr_base, dyn_info_t *dyn_info) {
	module_header_t *mod_header = (module_header_t *)&aslr_base[*(uint32_t*) &aslr_base[4]];
	Elf64_Dyn *dynamic = (Elf64_Dyn*) (((uint8_t*) mod_header) + mod_header->dynamic_off);
	uint64_t rela_offset = 0;
	uint64_t rela_size = 0;
	uint64_t rela_ent = 0;
	uint64_t rela_count = 0;
	bool found_rela = false;

	const char mod_magic[] = "MOD0";
	if(mod_header->magic != *((uint32_t*) mod_magic)) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_MODULE_HEADER;
	}
	
	while(dynamic->d_tag > 0) {
		switch(dynamic->d_tag) {
		case 2: // DT_PLTRELSZ
			break;
		case 3: // DT_PLTGOT
			break;
		case 4: // DT_HASH
			break;
		case 5: // DT_STRTAB
			break;
		case 6: // DT_SYMTAB
			break;
		case 7: // DT_RELA
			if(found_rela) {
				return LIBTRANSISTOR_ERR_TRNLD_DUPLICATE_DT_ENTRY;
			}
			rela_offset = dynamic->d_val;
			found_rela = true;
			break;
		case 8: // DT_RELASZ
			rela_size = dynamic->d_val;
			break;
		case 9: // DT_RELAENT
			rela_ent = dynamic->d_val;
			break;
		case 10: // DT_STRSZ
			break;
		case 11: // DT_SYMENT
			break;
		case 16: // DT_SYMBOLIC
			break;
		case 20: // DT_PLTREL
			break;
		case 23: // DT_JMPREL
			break;
		case 25: // DT_INIT_ARRAY
			if(dyn_info->init_array != NULL) {
				return LIBTRANSISTOR_ERR_TRNLD_DUPLICATE_DT_ENTRY;
			}
			dyn_info->init_array = (void (**)(void)) (aslr_base + dynamic->d_val);
			break;
		case 26: // DT_FINI_ARRAY
			if(dyn_info->fini_array != NULL) {
				return LIBTRANSISTOR_ERR_TRNLD_DUPLICATE_DT_ENTRY;
			}
			dyn_info->fini_array = (void (**)(void)) (aslr_base + dynamic->d_val);
			break;
		case 27: // DT_INIT_ARRAYSZ
			if(dyn_info->init_array_size != -1) {
				return LIBTRANSISTOR_ERR_TRNLD_DUPLICATE_DT_ENTRY;
			}
			dyn_info->init_array_size = dynamic->d_val;
			break;
		case 28: // DT_FINI_ARRAYSZ
			if(dyn_info->fini_array_size != -1) {
				return LIBTRANSISTOR_ERR_TRNLD_DUPLICATE_DT_ENTRY;
			}
			dyn_info->fini_array_size = dynamic->d_val;
			break;
		case 30: // DT_FLAGS
			// TODO
			break;
		case 0x6ffffef5: // DT_GNU_HASH
			break;
		case 0x6ffffff9: // DT_RELACOUNT
			rela_count = dynamic->d_val;
			break;
		default:
			if(RELOCATION_DEBUG) {
				dbg_printf("unrecognized dynamic entry: 0x%x\n", dynamic->d_tag);
			}
		}
		dynamic++;
	}
  
	if(rela_ent != 0x18) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELA_ENT;
	}
  
	if(rela_size != rela_count * rela_ent) {
		return LIBTRANSISTOR_ERR_TRNLD_INVALID_RELA_SIZE;
	}
  
	Elf64_Rela *rela_base = (Elf64_Rela*) (aslr_base + rela_offset);
	for(uint64_t i = 0; i < rela_count; i++) {
		Elf64_Rela rela = rela_base[i];
    
		switch(rela.r_reloc_type) {
		case 0x403: // R_AARCH64_RELATIVE
			if(rela.r_symbol != 0) {
				return LIBTRANSISTOR_ERR_TRNLD_RELA_SYMBOL_UNSUPPORTED;
			}
			*(void**)(aslr_base + rela.r_offset) = aslr_base + rela.r_addend;
			break;
		default:
			return LIBTRANSISTOR_ERR_TRNLD_UNRECOGNIZED_RELOC_TYPE;
		}
	}
	
	return RESULT_OK;
}

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
void phal_init();

int _libtransistor_start(loader_config_entry_t *config, uint64_t thread_handle, void *aslr_base) {
	dyn_info_t dyn_info;
	dyn_info.init_array = NULL;
	dyn_info.fini_array = NULL;
	dyn_info.init_array_size = -1;
	dyn_info.fini_array_size = -1;

	int ret;
	if((ret = relocate(aslr_base, &dyn_info)) != RESULT_OK) {
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

			ret = LIBTRANSISTOR_ERR_LEGACY_CONTEXT;
			goto restore_tls;
		}
		
		dbg_printf("found loader config");
		
		ret = lconfig_parse(config);
		if(ret != RESULT_OK) {
			goto restore_tls;
		}
		
		if(loader_config.main_thread == INVALID_HANDLE) {
			ret = HOMEBREW_ABI_KEY_NOT_PRESENT(LCONFIG_KEY_MAIN_THREAD_HANDLE);
			goto restore_tls;
		}
	} else {
		dbg_printf("no loader config");
	}

	if(_trn_runconf_heap_mode == _TRN_RUNCONF_HEAP_MODE_DEFAULT) {
		if(loader_config.heap_overridden) {
			_trn_runconf_heap_base = loader_config.heap_base;
			_trn_runconf_heap_size = loader_config.heap_size;
			_trn_runconf_heap_mode = _TRN_RUNCONF_HEAP_MODE_OVERRIDE;
		} else {
			_trn_runconf_heap_mode = _TRN_RUNCONF_HEAP_MODE_NORMAL;
		}
	}
	
	memset(get_tls(), 0, 0x200);
	main_thread.handle = loader_config.main_thread;
	main_thread.owns_stack = false;
	main_thread.arg = NULL;
	main_thread.pthread = NULL;
	_REENT_INIT_PTR(&main_thread.reent);
	get_tls()->thread = &main_thread;
	
	bool initialized_fs = false;
	bool ran_initializers = false;
	
	exit_mode_t exit_mode = setjmp(exit_jmpbuf);
	if(exit_mode == NOT_EXITING) {
		ret = as_init();
		if(ret != RESULT_OK) {
			goto restore_tls;
		}
		
		dbg_printf("init threads");
		phal_init();

		/*
		  Automatically initialize sm, since 99% of applications are going to be using it
		  and if they don't explicitly initialize it, each ipc module will initialize it,
		  use it, then immediately finalize it.
		*/
		if((ret = sm_init()) != RESULT_OK) {
			dbg_printf("failed to initialize sm: 0x%x", ret);
			goto restore_tls;
		}

		if(_trn_runconf_stdio_override  == _TRN_RUNCONF_STDIO_OVERRIDE_NONE) {
			if(loader_config.has_twili) {
				twili_pipe_t twili_out;
				if((ret = twili_init()) != RESULT_OK) {
					sm_finalize();
					goto restore_tls;
				}
				if((ret = twili_open_stdout(&twili_out)) != RESULT_OK) {
					twili_finalize();
					sm_finalize();
					goto restore_tls;
				}
				int fd = twili_pipe_fd(&twili_out);
				dup2(fd, STDOUT_FILENO);
				dbg_set_file(fd_file_get(fd));
				close(fd);
			} else if(loader_config.has_stdio_sockets) {
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
		} else if(_trn_runconf_stdio_override == _TRN_RUNCONF_STDIO_OVERRIDE_USB_SERIAL) {
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
		} else if(_trn_runconf_stdio_override == _TRN_RUNCONF_STDIO_OVERRIDE_SOCKETS) {
			int sock_fd;
			int e;
			dbg_connect(_trn_runconf_stdio_override_sockets_host,
			            _trn_runconf_stdio_override_sockets_port, &sock_fd);
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

		if(dyn_info.init_array != NULL) {
			if(dyn_info.init_array_size != -1) {
				for(size_t i = 0; i < dyn_info.init_array_size/sizeof(dyn_info.init_array[0]); i++) {
					dyn_info.init_array[i]();
				}
			}
		}
		ran_initializers = true;

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
		
		if(ran_initializers) {
			if(dyn_info.fini_array != NULL) {
				if(dyn_info.fini_array_size != -1) {
					for(size_t i = 0; i < dyn_info.fini_array_size/sizeof(dyn_info.fini_array[0]); i++) {
						dyn_info.fini_array[i]();
					}
				}
			}
		}

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
	if(loader_config.has_twili) {
		twili_finalize();
	}
	sm_finalize();

restore_tls:
	memcpy(get_tls(), tls_backup, 0x200);
	if(IS_NRO || ret == 0) {
		return ret;
	} else {
		fatal_init();
		fatal_transition_to_fatal_error(ret, 0);
		while(1) {}
		return ret;
	}
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
		.seek = NULL,
		.read = NULL,
		.write = dbg_log_write,
		.release = NULL,
	};
	return fd_create_file(&fops, NULL);
}
