# LIBTRANSISTOR HEADERS

libtransistor_HEADER_NAMES := alloc_pages.h audio.h display/graphic_buffer.h display/display.h display/surface.h display/parcel.h display/rect.h display/binder.h display/fence.h display/graphic_buffer_queue.h err/modules.h err.h fd.h fs/squashfs.h fs/fd.h fs/fs.h fs/inode.h fs/blobfd.h fs/mountfs.h fs/fspfs.h gfx/blit.h gfx/gfx.h gpu/gpu.h gpu/nv_ioc.h hid.h internal_util.h ipc/vi.h ipc/am.h ipc/nifm.h ipc/time.h ipc/nv.h ipc/ro.h ipc/fs/idirectory.h ipc/fs/ifilesystem.h ipc/fs/ifile.h ipc/fs/err.h ipc/bpc.h ipc/bsd.h ipc/fs.h ipc/audio.h ipc/sm.h ipc/pm.h ipc/hid.h ipc.h ipcserver.h loader_config.h nx.h stb_sprintf.h svc.h tls.h types.h util.h address_space.h ipc_helpers.h ipc/usb.h ipc/usb/ds/interface.h ipc/usb/ds/endpoint.h usb_serial.h mutex.h thread.h

DIST_TRANSISTOR_HEADERS := $(addprefix $(LIBTRANSISTOR_HOME)/include/libtransistor/,$(libtransistor_HEADER_NAMES))

$(LIBTRANSISTOR_HOME)/include/%: $(SOURCE_ROOT)/include/%
	install -d $(@D)
	install $< $@

.PHONY: dist_transistor_headers
dist_transistor_headers: $(DIST_TRANSISTOR_HEADERS)
