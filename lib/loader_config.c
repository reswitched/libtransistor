#include<libtransistor/loader_config.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/util.h>
#include<libtransistor/err.h>
#include<libtransistor/svc.h>

#include<string.h>

static uint64_t nro_syscalls[2] = {    0x83fffffffffe,        0x1000c0000};
static uint64_t nso_syscalls[2] = {0xffffffffffffffff, 0xffffffffffffffff};

loader_config_t loader_config;

void lconfig_init_default(uint64_t thread_handle) {
	loader_config.main_thread = thread_handle;
	loader_config.heap_overridden = false;
	loader_config.num_service_overrides = 0;
	
	char *argv_default[] = {"unknown", NULL};
	loader_config.argv = argv_default;
	loader_config.argc = 1;

	memcpy(loader_config.syscall_hints, IS_NRO ? nro_syscalls : nso_syscalls,
	       IS_NRO ? sizeof(nro_syscalls) : sizeof(nso_syscalls));

	loader_config.has_applet_type = false;
	loader_config.applet_type = LCONFIG_APPLET_TYPE_UNKNOWN;

	loader_config.applet_workaround_active = false;

	loader_config.has_stdio_sockets = false;
}

result_t lconfig_parse(loader_config_entry_t *config) {
	result_t r;
	
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

			memory_info_t mem_info;
			uint32_t page_info;

			void *validation_head = loader_config.heap_base;

			while(validation_head < loader_config.heap_base + loader_config.heap_size) {
				if((r = svcQueryMemory(&mem_info, &page_info, validation_head)) != RESULT_OK) {
					return r;
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
			}
				
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
			loader_config.syscall_hints[0] = entry->syscall_available_hint.hints[0];
			loader_config.syscall_hints[1] = entry->syscall_available_hint.hints[1];
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
			break;

		case LCONFIG_KEY_PROCESS_HANDLE:
			loader_config.has_process_handle = true;
			loader_config.process_handle = entry->process_handle.process_handle;
			break;
			
		case LCONFIG_KEY_ALLOC_PAGES:
			loader_config.has_alloc_pages = true;
			loader_config.alloc_pages = entry->alloc_pages.alloc_pages;
			loader_config.free_pages = entry->alloc_pages.free_pages;
			break;

		case LCONFIG_KEY_LOCK_REGION:
			if((r = ap_lock_region(entry->lock_region.addr, entry->lock_region.size)) != RESULT_OK) {
				return r;
			}
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

result_t lconfig_has_syscall(uint8_t syscall) {
	if(syscall < 0x40) {
		return (loader_config.syscall_hints[0] & (1 << syscall)) == 0 ? LIBTRANSISTOR_ERR_NEEDS_SYSCALL(syscall) : RESULT_OK;
	} else {
		return (loader_config.syscall_hints[1] & (1 << (syscall - 0x40))) == 0 ? LIBTRANSISTOR_ERR_NEEDS_SYSCALL(syscall) : RESULT_OK;
	}
}

result_t lconfig_has_syscalls(const uint8_t *syscalls) {
	for(; *syscalls != 0; syscalls++) {
		result_t r;
		if((r = lconfig_has_syscall(*syscalls)) != RESULT_OK) {
			return r;
		}
	}
	return RESULT_OK;
}
