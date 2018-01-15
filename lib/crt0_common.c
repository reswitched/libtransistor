#include<libtransistor/loader_config.h>
#include<libtransistor/util.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/bsd.h>

#include<sys/socket.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<setjmp.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

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

// defined in crt0.nxo.S, mostly to avoid using the GOT before we relocate its entries
extern module_header_t *_get_module_header();

static void (**init_array)(void) = NULL;
static void (**fini_array)(void) = NULL;

static ssize_t init_array_size = -1;
static ssize_t fini_array_size = -1;

static bool relocate(uint8_t *aslr_base) {
	module_header_t *mod_header = _get_module_header();
	Elf64_Dyn *dynamic = (Elf64_Dyn*) (((uint8_t*) mod_header) + mod_header->dynamic_off);
	uint64_t rela_offset = 0;
	uint64_t rela_size = 0;
	uint64_t rela_ent = 0;
	uint64_t rela_count = 0;
	bool found_rela = false;
	
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
			if(init_array != NULL) {
				return true;
			}
			init_array = (void (**)(void)) (aslr_base + dynamic->d_val);
			break;
		case 26: // DT_FINI_ARRAY
			if(fini_array != NULL) {
				return true;
			}
			fini_array = (void (**)(void)) (aslr_base + dynamic->d_val);
			break;
		case 27: // DT_INIT_ARRAYSZ
			if(init_array_size != -1) {
				return true;
			}
			init_array_size = dynamic->d_val;
			break;
		case 28: // DT_FINI_ARRAYSZ
			if(fini_array_size != -1) {
				return true;
			}
			fini_array_size = dynamic->d_val;
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

static FILE bsslog_stdout;
static int bsslog_write(struct _reent *reent, void *v, const char *ptr, int len) {
	log_string(ptr, len);
	return len;
}

#define DEFAULT_NOCONTEXT_HEAP_SIZE 0x400000

static jmp_buf exit_jmpbuf;
static int exit_value;

static void __attribute__((__noreturn__)) default_exit(int result_code) {
	svcExitProcess(result_code);
}

loader_config_t loader_config;

static bool nro_syscalls[0xFF] = {};
static bool nso_syscalls[0xFF] = {};

static void lconfig_init_default(uint64_t thread_handle);
static void lconfig_parse(loader_config_entry_t *config);
static void setup_stdio_socket(const char *name, int socket_fd, int target_fd);

int _libtransistor_start(loader_config_entry_t *config, uint64_t thread_handle, void *aslr_base) {
	if(relocate(aslr_base)) {
		return -4;
	}

	int ret;
	
	dbg_printf("aslr base: %p", aslr_base);
	dbg_printf("config: %p", config);

	// Initialize default behaviour for loader config
	lconfig_init_default(thread_handle);
	
	// parse loader config, if present
	if(config != NULL) {
		dbg_printf("found loader config");

		lconfig_parse(config);
		
		if(loader_config.main_thread == INVALID_HANDLE) {
			loader_config.return_func(HOMEBREW_ABI_KEY_NOT_PRESENT(LCONFIG_KEY_MAIN_THREAD_HANDLE));
		}
	} else {
		dbg_printf("no loader config");
	}

	dbg_printf("init bsslogger stdio");
	bsslog_stdout._write = bsslog_write;
	bsslog_stdout._flags = __SWR | __SNBF;
	bsslog_stdout._bf._base = (void*) 1;

	/*
	  Automatically initialize sm, since 99% of applications are going to be using it
	  and if they don't explicitly initialize it, each ipc module will initialize it,
	  use it, then immediately finalize it.
	 */
	if((ret = sm_init()) != RESULT_OK) {
		dbg_printf("failed to initialize sm: 0x%x", ret);
		loader_config.return_func(ret);
	}
	
	if(loader_config.has_stdio_sockets) {
		if((ret = bsd_init_ex(true, loader_config.socket_service)) != RESULT_OK) {
			sm_finalize();
			loader_config.return_func(ret);
		}

		dbg_printf("using socklog stdio");
		setup_stdio_socket("stdout", loader_config.socket_stdout, STDOUT_FILENO);
		setup_stdio_socket("stdin",  loader_config.socket_stdin,  STDIN_FILENO);
		setup_stdio_socket("stderr", loader_config.socket_stderr, STDERR_FILENO);
	} else {
		// TODO: Create a fake FD for bsslog
		dbg_printf("using bsslog stdout");
		printf("_"); // init stdout
		getchar(); // init stdin
		stdout = &bsslog_stdout;
		stderr = &bsslog_stdout;
	}
	dbg_printf("set up stdout");
	
	if(setjmp(exit_jmpbuf) == 0) {
		if(init_array != NULL) {
			if(init_array_size == -1) {
				return true;
			}
			for(size_t i = 0; i < init_array_size/sizeof(init_array[0]); i++) {
				init_array[i]();
			}
		}
		
		ret = main(loader_config.argc, loader_config.argv);
		exit(ret);
	} else {
		ret = exit_value;
	}

	if(fini_array != NULL) {
		if(fini_array_size == -1) {
			return true;
		}
		for(size_t i = 0; i < fini_array_size/sizeof(fini_array[0]); i++) {
			fini_array[i]();
		}
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

	loader_config.return_func(ret);
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

static void lconfig_init_default(uint64_t thread_handle) {
	loader_config.main_thread = thread_handle;
	loader_config.return_func = default_exit;
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

static void lconfig_parse(loader_config_entry_t *config) {
	result_t ret;
	
	for(loader_config_entry_t *entry = config; entry->key != LCONFIG_KEY_END_OF_LIST; entry++) {
		switch(entry->key) {
				
		case LCONFIG_KEY_MAIN_THREAD_HANDLE:
			loader_config.main_thread = entry->main_thread_handle.main_thread_handle;
			break;
				
		case LCONFIG_KEY_LOADER_RETURN_ADDR:
			loader_config.return_func = entry->loader_return_addr.return_func;
			break;

		case LCONFIG_KEY_OVERRIDE_HEAP: {
			loader_config.heap_overridden = true;
			loader_config.heap_base = entry->override_heap.heap_base;
			loader_config.heap_size = entry->override_heap.heap_size;

			memory_info_t mem_info;
			uint32_t page_info;

			void *validation_head = loader_config.heap_base;

			while(validation_head < loader_config.heap_base + loader_config.heap_size) {
				if((ret = svcQueryMemory(&mem_info, &page_info, validation_head)) != RESULT_OK) {
					loader_config.return_func(ret);
				}
					
				if(!(mem_info.memory_type == 4 || mem_info.memory_type == 5 || mem_info.memory_type == 9)) {
					loader_config.return_func(HOMEBREW_ABI_KEY_INVALID(LCONFIG_KEY_OVERRIDE_HEAP));
				}

				if(mem_info.permission != 3) {
					loader_config.return_func(HOMEBREW_ABI_KEY_INVALID(LCONFIG_KEY_OVERRIDE_HEAP));
				}

				if(mem_info.device_ref_count != 0 || mem_info.ipc_ref_count != 0) {
					loader_config.return_func(HOMEBREW_ABI_KEY_INVALID(LCONFIG_KEY_OVERRIDE_HEAP));
				}
					
				validation_head+= mem_info.size;
			}
				
			break; }
				
		case LCONFIG_KEY_OVERRIDE_SERVICE:
			if(loader_config.num_service_overrides >= 32) {
				loader_config.return_func(HOMEBREW_ABI_KEY_INVALID(LCONFIG_KEY_OVERRIDE_SERVICE));
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
				loader_config.return_func(HOMEBREW_ABI_KEY_INVALID(entry->key));
			}
			// TODO: initialize bsd
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
				loader_config.return_func(HOMEBREW_ABI_UNRECOGNIZED_KEY(entry->key));
			}
			break; }
		}
	}
}
