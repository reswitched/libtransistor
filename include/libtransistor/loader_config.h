#pragma once

// homebrew ABI as of http://switchbrew.org/index.php?title=Homebrew_ABI&oldid=3461

#include<libtransistor/types.h>
#include<libtransistor/ipc.h>

#include<assert.h>

extern bool IS_NRO;

typedef enum {
	LOADER_CONFIG_FLAG_RECOGNITION_MANDATORY = BIT(0),
} loader_config_flags_t;

typedef enum {
	LCONFIG_KEY_END_OF_LIST = 0,
	LCONFIG_KEY_MAIN_THREAD_HANDLE = 1,
	LCONFIG_KEY_NEXT_LOAD_PATH = 2,
	LCONFIG_KEY_OVERRIDE_HEAP = 3,
	LCONFIG_KEY_OVERRIDE_SERVICE = 4,
	LCONFIG_KEY_ARGV = 5,
	LCONFIG_KEY_SYSCALL_AVAILABLE_HINT = 6,
	LCONFIG_KEY_APPLET_TYPE = 7,
	LCONFIG_KEY_APPLET_WORKAROUND = 8,
	LCONFIG_KEY_STDIO_SOCKETS = 9,
} loader_config_key_t;

typedef enum {
	LCONFIG_APPLET_TYPE_APPLICATION = 0,
	LCONFIG_APPLET_TYPE_SYSTEM_APPLET = 1,
	LCONFIG_APPLET_TYPE_LIBRARY_APPLET = 2,
	LCONFIG_APPLET_TYPE_OVERLAY_APPLET = 3,
	LCONFIG_APPLET_TYPE_SYSTEM_APPLICATION = 4,
	
	LCONFIG_APPLET_TYPE_UNKNOWN = 0xFFFFFFFFFFFFFFFF,
} loader_config_applet_type_t;

typedef enum {
	LCONFIG_SOCKET_SERVICE_BSD_U = 0,
	LCONFIG_SOCKET_SERVICE_BSD_S = 1,
	LCONFIG_SOCKET_SERVICE_MAX = 2,

	LCONFIG_SOCKET_SERVICE_UNSPECIFIED = 0xFFFFFFFF,
} loader_config_socket_service_t;

typedef struct {
	uint64_t service_name;
	handle_t service_handle;
} loader_config_service_override_t;

typedef struct {
	uint32_t key;
	uint32_t flags;
	union {
		uint64_t value[2];
		struct {
		} end_of_list;
		struct {
			handle_t main_thread_handle;
		} main_thread_handle;
		struct {
			char (*nro_path)[512];
			char (*argv_str)[2048];
		} next_load_path;
		struct {
			void *heap_base;
			size_t heap_size;
		} override_heap;
		struct {
			loader_config_service_override_t override;
		} override_service;
		struct {
			uint64_t argc;
			char **argv;
		} argv;
		struct {
			uint8_t hints[16];
		} syscall_available_hint;
		struct {
			loader_config_applet_type_t applet_type;
		} applet_type;
		struct {
			aruid_t aruid;
		} applet_workaround;
		struct {
			// naming these stdout, stdin, and stderr conflicts with newlib macros
			int32_t s_stdout, s_stdin, s_stderr;
			loader_config_socket_service_t socket_service;
		} stdio_sockets;
	};
} loader_config_entry_t;

typedef struct {
	// MainThreadHandle
	handle_t main_thread;
	
	// NextLoadPath
	//   ignored

	// OverrideHeap
	bool heap_overridden;
	void *heap_base;
	size_t heap_size;

	// OverrideService
	int num_service_overrides;
	loader_config_service_override_t service_overrides[32];
	
	// Argv
	char **argv;
	int argc;

	// SyscallAvailableHint
	bool syscalls_available[255]; // not really concerned about space efficiency

	// AppletType
	bool has_applet_type;
	loader_config_applet_type_t applet_type;

	// AppletWorkaround
	bool applet_workaround_active;
	aruid_t applet_workaround_aruid;

	// StdioSockets
	bool has_stdio_sockets;
	int socket_stdout, socket_stdin, socket_stderr;
	loader_config_socket_service_t socket_service;
	
} loader_config_t;

extern loader_config_t loader_config;

static_assert(sizeof(loader_config_entry_t) == 0x18, "loader config entry size should be 0x18 bytes");
