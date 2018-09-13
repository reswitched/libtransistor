# LIBTRANSISTOR HEADERS

libtransistor_HEADER_NAMES := \
	address_space.h \
	alloc_pages.h \
	audio.h \
	collections/list.h \
	condvar.h \
	display/binder.h \
	display/display.h \
	display/fence.h \
	display/graphic_buffer.h \
	display/graphic_buffer_queue.h \
	display/parcel.h \
	display/rect.h \
	display/surface.h \
	environment.h \
	err.h \
	err/modules.h \
	fd.h \
	fs/blobfd.h \
	fs/fs.h \
	fs/fspfs.h \
	fs/inode.h \
	fs/mountfs.h \
	fs/squashfs.h \
	gfx/blit.h \
	gfx/gfx.h \
	gpu/gpu.h \
	gpu/nv_ioc.h \
	hid.h \
	internal_util.h \
	ipc/am.h \
	ipc/audio.h \
	ipc/bpc.h \
	ipc/bsd.h \
	ipc/fatal.h \
	ipc/fs/err.h \
	ipc/fs.h \
	ipc/fs/idirectory.h \
	ipc/fs/ifile.h \
	ipc/fs/ifilesystem.h \
	ipc.h \
	ipc_helpers.h \
	ipc/hid.h \
	ipc/nifm.h \
	ipc/nv.h \
	ipc/pm.h \
	ipc/ro.h \
	ipcserver.h \
	ipc/sm.h \
	ipc/time.h \
	ipc/twili.h \
	ipc/usb/ds/endpoint.h \
	ipc/usb/ds/interface.h \
	ipc/usb.h \
	ipc/vi.h \
	ld/elf.h \
	ld/internal.h \
	ld/ld.h \
	ld/loaders.h \
	ld/module.h \
	loader_config.h \
	mutex.h \
	nx.h \
	runtime_config.h \
	stb_sprintf.h \
	svc.h \
	thread.h \
	tls.h \
	types.h \
	usb_serial.h \
	util.h \
	waiter.h

libtransistor_CPP_HEADER_NAMES := \
	address_space.hpp \
	ipcclient.hpp \
	ipc/hid.hpp \
	ipc.hpp \
	ipcserver.hpp \
	ipc/sm.hpp \
	ipc/usb_ds.hpp \
	ipc/usb.hpp \
	nx.hpp \
	svc.hpp \
	types.hpp \
	waiter.hpp

DIST_TRANSISTOR_HEADERS := $(addprefix $(LIBTRANSISTOR_HOME)/include/libtransistor/,$(libtransistor_HEADER_NAMES))
DIST_TRANSISTOR_CPP_HEADERS := $(DIST_TRANSISTOR_HEADERS) $(addprefix $(LIBTRANSISTOR_HOME)/include/libtransistor/cpp/,$(libtransistor_CPP_HEADER_NAMES)) $(DIST_NEITHER_HEADERS)

$(LIBTRANSISTOR_HOME)/include/%: $(SOURCE_ROOT)/include/%
	install -d $(@D)
	install $< $@

.PHONY: dist_transistor_headers dist_transistor_cpp_headers
dist_transistor_headers: $(DIST_TRANSISTOR_HEADERS)
dist_transistor_cpp_headers: $(DIST_TRANSISTOR_CPP_HEADERS)
