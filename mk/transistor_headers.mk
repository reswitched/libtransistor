# LIBTRANSISTOR HEADERS

libtransistor_HEADER_NAMES := alloc_pages.h gpu/gpu.h gpu/nv_ioc.h ipc.h fs/squashfs.h fs/fd.h fs/fs.h fs/inode.h fs/blobfd.h fd.h tls.h nx.h ipcserver.h internal_util.h types.h loader_config.h audio.h stb_sprintf.h hid.h err.h display/graphic_buffer.h display/display.h display/surface.h display/parcel.h display/rect.h display/binder.h display/fence.h display/graphic_buffer_queue.h ipc/vi.h ipc/am.h ipc/nifm.h ipc/time.h ipc/nv.h ipc/ro.h ipc/bpc.h ipc/bsd.h ipc/audio.h ipc/sm.h ipc/pm.h ipc/hid.h util.h svc.h gfx/blit.h gfx/gfx.h

DIST_TRANSISTOR_HEADERS := $(addprefix $(LIBTRANSISTOR_HOME)/include/libtransistor/,$(libtransistor_HEADER_NAMES))

$(LIBTRANSISTOR_HOME)/include/%: $(SOURCE_ROOT)/include/%
	install -d $(@D)
	install $< $@

.PHONY: dist_transistor_headers
dist_transistor_headers: $(DIST_TRANSISTOR_HEADERS)
