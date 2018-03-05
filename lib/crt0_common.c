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

#include<sys/socket.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<setjmp.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<rthread.h>

#include "default_squashfs_image.h"
#include "squashfs/squashfuse.h"


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

static bool relocate(uint8_t *aslr_base, dyn_info_t *dyn_info) {
	module_header_t *mod_header = (module_header_t *)&aslr_base[*(uint32_t*) &aslr_base[4]];
	Elf64_Dyn *dynamic = (Elf64_Dyn*) (((uint8_t*) mod_header) + mod_header->dynamic_off);
	uint64_t rela_offset = 0;
	uint64_t rela_size = 0;
	uint64_t rela_ent = 0;
	uint64_t rela_count = 0;
	bool found_rela = false;

	const char mod_magic[] = "MOD0";
	if(mod_header->magic != *((uint32_t*) mod_magic)) {
		return true;
	}
	
	while(dynamic->d_tag > 0) {
		switch(dynamic->d_tag) {
		case 4: // DT_HASH
			break;
		case 5: // DT_STRTAB
			break;
		case 6: // DT_SYMTAB
			break;
		case 7: // DT_RELA
			if(found_rela) {
				return true;
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
		case 25: // DT_INIT_ARRAY
			if(dyn_info->init_array != NULL) {
				return true;
			}
			dyn_info->init_array = (void (**)(void)) (aslr_base + dynamic->d_val);
			break;
		case 26: // DT_FINI_ARRAY
			if(dyn_info->fini_array != NULL) {
				return true;
			}
			dyn_info->fini_array = (void (**)(void)) (aslr_base + dynamic->d_val);
			break;
		case 27: // DT_INIT_ARRAYSZ
			if(dyn_info->init_array_size != -1) {
				return true;
			}
			dyn_info->init_array_size = dynamic->d_val;
			break;
		case 28: // DT_FINI_ARRAYSZ
			if(dyn_info->fini_array_size != -1) {
				return true;
			}
			dyn_info->fini_array_size = dynamic->d_val;
			break;
		case 30: // DT_FLAGS
			// TODO
			break;
		case 0x6ffffff9: // DT_RELACOUNT
			rela_count = dynamic->d_val;
			break;
		default:
			dbg_printf("unknown dynamic tag: %d\n", dynamic->d_tag);
		}
		dynamic++;
	}
  
	if(rela_ent != 0x18) {
		return true;
	}
  
	if(rela_size != rela_count * rela_ent) {
		return true;
	}
  
	Elf64_Rela *rela_base = (Elf64_Rela*) (aslr_base + rela_offset);
	for(uint64_t i = 0; i < rela_count; i++) {
		Elf64_Rela rela = rela_base[i];
    
		switch(rela.r_reloc_type) {
		case 0x403: // R_AARCH64_RELATIVE
			if(rela.r_symbol != 0) {
				return true;
			}
			*(void**)(aslr_base + rela.r_offset) = aslr_base + rela.r_addend;
			break;
		default:
			return true;
		}
	}
	
	return false;
}

static size_t dbg_log_write(void *v, const char *ptr, size_t len) {
	log_string(ptr, len);
	return len;
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

static jmp_buf exit_jmpbuf;
static int exit_value;

loader_config_t loader_config;

static bool nro_syscalls[0xFF] = {};
static bool nso_syscalls[0xFF] = {};

static uint8_t tls_backup[0x200];

bool _crt0_kludge_skip_cleanup = false; // TODO: REMOVE THIS ASAP


static void lconfig_init_default(uint64_t thread_handle);
static result_t lconfig_parse(loader_config_entry_t *config);

static void setup_stdio_socket(const char *name, int socket_fd, int target_fd);
static int make_dbg_log_fd();

extern void _cleanup_mapped_heap();

int _libtransistor_start(loader_config_entry_t *config, uint64_t thread_handle, void *aslr_base) {
	dyn_info_t dyn_info;
	dyn_info.init_array = NULL;
	dyn_info.fini_array = NULL;
	dyn_info.init_array_size = -1;
	dyn_info.fini_array_size = -1;
	
	if(relocate(aslr_base, &dyn_info)) {
		return -4;
	}
	
	int ret;

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

	dbg_printf("backup tls");
	memcpy(tls_backup, get_tls(), 0x200);
	memset(get_tls(), 0, 0x200);
	
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

	if(loader_config.has_stdio_sockets) {
		if((ret = bsd_init_ex(true, loader_config.socket_service)) != RESULT_OK) {
			sm_finalize();
			goto restore_tls;
		}

		dbg_printf("using socklog stdio");
		setup_stdio_socket("stdout", loader_config.socket_stdout, STDOUT_FILENO);
		setup_stdio_socket("stdin",  loader_config.socket_stdin,  STDIN_FILENO);
		setup_stdio_socket("stderr", loader_config.socket_stderr, STDERR_FILENO);
		dbg_set_bsd_log(loader_config.socket_stdout);
	} else {

		// TODO: Create a fake FD for bsslog
		dbg_printf("using bsslog stdout");
		int fd = make_dbg_log_fd();
		if(fd < 0) {
			dbg_printf("error making debug log fd");
		} else {
			dup2(fd, STDOUT_FILENO);
			dup2(fd, STDERR_FILENO);
		}
	}
	dbg_printf("set up stdout");

	if(setup_fs()) {
		ret = -14;
		goto fail_bsd;
	}
	
	if(setjmp(exit_jmpbuf) == 0) {
		if(dyn_info.init_array != NULL) {
			if(dyn_info.init_array_size != -1) {
				for(size_t i = 0; i < dyn_info.init_array_size/sizeof(dyn_info.init_array[0]); i++) {
					dyn_info.init_array[i]();
				}
			}
		}

		ret = main(loader_config.argc, loader_config.argv);
		exit(ret);
	} else {
		ret = exit_value;
	}

	if(!_crt0_kludge_skip_cleanup) { // TODO: remove cleanup kludge ASAP
		// Clean up FS
		root_inode.ops->release(root_inode.data);

		dbg_set_bsd_log(-1);

		if(dyn_info.fini_array != NULL) {
			if(dyn_info.fini_array_size != -1) {
				for(size_t i = 0; i < dyn_info.fini_array_size/sizeof(dyn_info.fini_array[0]); i++) {
					dyn_info.fini_array[i]();
				}
			}
		}

		dbg_printf("cleaning up mapped heap");
		_cleanup_mapped_heap();
		dbg_printf("cleaned heap");
	} else {
		printf("crt0: cleanup kludge active, please fix this ASAP\n");
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
	longjmp(exit_jmpbuf, 1);
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
	static struct file_operations fops = {
		.write = dbg_log_write
	};
	return fd_create_file(&fops, NULL);
}

static void lconfig_init_default(uint64_t thread_handle) {
	loader_config.main_thread = thread_handle;
	loader_config.heap_overridden = false;
	loader_config.num_service_overrides = 0;
	
	char *argv_default[] = {"unknown", NULL};
	loader_config.argv = argv_default;
	loader_config.argc = 1;

	memcpy(loader_config.syscalls_available, IS_NRO ? nro_syscalls : nso_syscalls,
	       IS_NRO ? sizeof(nro_syscalls) : sizeof(nso_syscalls));

	loader_config.has_applet_type = false;
	loader_config.applet_type = LCONFIG_APPLET_TYPE_UNKNOWN;

	loader_config.applet_workaround_active = false;

	loader_config.has_stdio_sockets = false;
}

static result_t lconfig_parse(loader_config_entry_t *config) {
	for(loader_config_entry_t *entry = config; entry->key != LCONFIG_KEY_END_OF_LIST; entry++) {
		switch(entry->key) {
				
		case LCONFIG_KEY_MAIN_THREAD_HANDLE:
			loader_config.main_thread = entry->main_thread_handle.main_thread_handle;
			break;
				
		case LCONFIG_KEY_NEXT_LOAD_PATH:
			// ignored
			break;

		case LCONFIG_KEY_OVERRIDE_HEAP: {
			loader_config.heap_overridden = true;
			loader_config.heap_base = entry->override_heap.heap_base;
			loader_config.heap_size = entry->override_heap.heap_size;

			/*memory_info_t mem_info;
			uint32_t page_info;

			void *validation_head = loader_config.heap_base;

			while(validation_head < loader_config.heap_base + loader_config.heap_size) {
				if((ret = svcQueryMemory(&mem_info, &page_info, validation_head)) != RESULT_OK) {
					return ret;
				}
					
				if(!(mem_info.memory_type == 4 || mem_info.memory_type == 5 || mem_info.memory_type == 9)) {
					return HOMEBREW_ABI_KEY_INVALID(LCONFIG_KEY_OVERRIDE_HEAP);
				}

				if(mem_info.permission != 3) {
					return HOMEBREW_ABI_KEY_INVALID(LCONFIG_KEY_OVERRIDE_HEAP);
				}

				if(mem_info.device_ref_count != 0 || mem_info.ipc_ref_count != 0) {
					return HOMEBREW_ABI_KEY_INVALID(LCONFIG_KEY_OVERRIDE_HEAP);
				}
					
				validation_head+= mem_info.size;
				}*/
				
			break; }
				
		case LCONFIG_KEY_OVERRIDE_SERVICE:
			if(loader_config.num_service_overrides >= 32) {
				return HOMEBREW_ABI_KEY_INVALID(LCONFIG_KEY_OVERRIDE_SERVICE);
			}
			loader_config.service_overrides[loader_config.num_service_overrides++] = entry->override_service.override;
			break;
				
		case LCONFIG_KEY_ARGV:
			loader_config.argc = entry->argv.argc;
			loader_config.argv = entry->argv.argv;
			break;
				
		case LCONFIG_KEY_SYSCALL_AVAILABLE_HINT:
			for(size_t i = 0; i < ARRAY_LENGTH(entry->syscall_available_hint.hints); i++) {
				uint8_t hint = entry->syscall_available_hint.hints[i];
				if(hint != 0xFF) {
					loader_config.syscalls_available[hint] = true;
				}
			}
			break;
				
		case LCONFIG_KEY_APPLET_TYPE:
			loader_config.has_applet_type = true;
			loader_config.applet_type = entry->applet_type.applet_type;
			break;
				
		case LCONFIG_KEY_APPLET_WORKAROUND:
			loader_config.applet_workaround_active = true;
			loader_config.applet_workaround_aruid = entry->applet_workaround.aruid;
			break;

		case LCONFIG_KEY_STDIO_SOCKETS:
			loader_config.has_stdio_sockets = true;
			loader_config.socket_stdout = entry->stdio_sockets.s_stdout;
			loader_config.socket_stdin  = entry->stdio_sockets.s_stdin;
			loader_config.socket_stderr = entry->stdio_sockets.s_stderr;
			loader_config.socket_service = entry->stdio_sockets.socket_service;

			if(loader_config.socket_service >= LCONFIG_SOCKET_SERVICE_MAX) {
				return HOMEBREW_ABI_KEY_INVALID(entry->key);
			}
			// TODO: initialize bsd
			break;

		case LCONFIG_KEY_ALLOC_PAGES:
			loader_config.has_alloc_pages = true;
			loader_config.alloc_pages = entry->alloc_pages.alloc_pages;
			loader_config.free_pages = entry->alloc_pages.free_pages;
			break;

		case LCONFIG_KEY_LOCK_REGION:
			ap_lock_region(entry->lock_region.addr, entry->lock_region.size);
			break;
			
		default: {
			bool recognition_mandatory = entry->flags & LOADER_CONFIG_FLAG_RECOGNITION_MANDATORY;
			if(recognition_mandatory) {
				dbg_printf("ERR: unrecognized config key %d\n", entry->key);
			} else {
				dbg_printf("WARN: unrecognized config key %d\n", entry->key);
			}

			dbg_printf("  flags: 0x%x\n", entry->flags);
			dbg_printf("  value[0]: 0x%x\n", entry->value[0]);
			dbg_printf("  value[1]: 0x%x\n", entry->value[1]);
				
			if(recognition_mandatory) {
				return HOMEBREW_ABI_UNRECOGNIZED_KEY(entry->key);
			}
			break; }
		}
	}

	return RESULT_OK;
}
