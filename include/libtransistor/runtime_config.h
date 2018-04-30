/**
 * @file libtransistor/runtime_config.h
 * @brief Runtime configuration
 *
 * Any global variables here are defined as weak
 * in libtransistor and can be overridden by an
 * application.
 */

#pragma once

typedef enum {
	_TRN_RUNCONF_STDIO_OVERRIDE_NONE, ///< Determine stdout via HBABI
	_TRN_RUNCONF_STDIO_OVERRIDE_USB_SERIAL, ///< Force stdout over usb_serial
	_TRN_RUNCONF_STDIO_OVERRIDE_SOCKETS, ///< Force stdout over sockets
} runconf_stdio_override_t;

extern runconf_stdio_override_t _trn_runconf_stdio_override;
extern const char *_trn_runconf_stdio_override_sockets_host;
extern const char *_trn_runconf_stdio_override_sockets_port;

typedef enum {
	_TRN_RUNCONF_HEAP_MODE_DEFAULT, ///< Use heap from HBABI, or default to HEAP_MODE_NORMAL.
	_TRN_RUNCONF_HEAP_MODE_NORMAL, ///< Force using svcSetHeapSize, even if HBABI specifies otherwise.
	_TRN_RUNCONF_HEAP_MODE_OVERRIDE, ///< Force heap extents, even if HBABI specifies otherwise.
} runconf_heap_mode_t;

extern runconf_heap_mode_t _trn_runconf_heap_mode;
extern void *_trn_runconf_heap_base;
extern size_t _trn_runconf_heap_size;
