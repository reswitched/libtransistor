/**
 * @file libtransistor/nx.h
 * @brief Central Switch header. Includes all others.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// core headers
#include<libtransistor/types.h>
#include<libtransistor/loader_config.h>
#include<libtransistor/runtime_config.h>
#include<libtransistor/environment.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/address_space.h>
#include<libtransistor/err.h>
#include<libtransistor/err/modules.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc_helpers.h>
#include<libtransistor/tls.h>
#include<libtransistor/util.h>
#include<libtransistor/mutex.h>
#include<libtransistor/thread.h>

// filesystem
#include<libtransistor/fd.h>
#include<libtransistor/fs/fs.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/fs/blobfd.h>
#include<libtransistor/fs/mountfs.h>
#include<libtransistor/fs/fspfs.h>
#include<libtransistor/fs/squashfs.h>

// services
#include<libtransistor/ipc/am.h>
#include<libtransistor/ipc/audio.h>
#include<libtransistor/ipc/bpc.h>
#include<libtransistor/ipc/bsd.h>
#include<libtransistor/ipc/fatal.h>
#include<libtransistor/ipc/fs.h>
#include<libtransistor/ipc/hid.h>
#include<libtransistor/ipc/nifm.h>
#include<libtransistor/ipc/nv.h>
#include<libtransistor/ipc/pm.h>
#include<libtransistor/ipc/ro.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/time.h>
#include<libtransistor/ipc/twili.h>
#include<libtransistor/ipc/usb.h>
#include<libtransistor/ipc/vi.h>

// high-level
#include<libtransistor/collections/list.h>
#include<libtransistor/gpu/gpu.h>
#include<libtransistor/gfx/gfx.h>
#include<libtransistor/display/display.h>
#include<libtransistor/display/surface.h>
#include<libtransistor/display/fence.h>
#include<libtransistor/hid.h>
#include<libtransistor/audio.h>
#include<libtransistor/waiter.h>
#include<libtransistor/ipcserver.h>
#include<libtransistor/usb_serial.h>
#include<libtransistor/ipcserver.h>

// linking
#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>

#ifdef __cplusplus
}
#endif
