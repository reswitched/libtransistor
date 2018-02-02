# LIBTRANSISTOR

libtransistor_OBJECT_NAMES := crt0_common.o svc.o ipc.o tls.o util.o ipc/sm.o ipc/bsd.o ipc/nv.o ipc/hid.o ipc/ro.o ipc/nifm.o hid.o ipc/vi.o display/binder.o display/parcel.o display/surface.o gpu/gpu.o ipc/am.o display/graphic_buffer_queue.o display/display.o gfx/blit.o ipc/time.o syscalls/syscalls.o syscalls/fd.o syscalls/sched.o syscalls/socket.o lz4.o squashfs/cache.o squashfs/decompress.o squashfs/dir.o squashfs/file.o squashfs/fs.o squashfs/hash.o squashfs/nonstd-pread.o squashfs/nonstd-stat.o squashfs/stack.o squashfs/swap.o squashfs/table.o squashfs/traverse.o squashfs/util.o squashfs/xattr.o fs/blobfd.o fs/squashfs.o fs/fs.o ipc/audio.o ipc/bpc.o ipcserver.o strtold.o
libtransistor_OBJECT_FILES := $(addprefix $(LIBTRANSISTOR_HOME)/build/lib/,$(libtransistor_OBJECT_NAMES))

libtransistor_WARNINGS := -Wall -Wextra -Werror-implicit-function-declaration -Wno-unused-parameter -Wno-unused-command-line-argument

# ARCHIVE RULES

$(LIBTRANSISTOR_NRO_DEP): $(LIBTRANSISTOR_HOME)/build/lib/crt0.nro.o $(libtransistor_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

$(LIBTRANSISTOR_NSO_DEP): $(LIBTRANSISTOR_HOME)/build/lib/crt0.nso.o $(libtransistor_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

# BUILD RULES

# Disable stack protector for crt0_common
$(LIBTRANSISTOR_HOME)/build/lib/crt0_common.o $(LIBTRANSISTOR_HOME)/build/lib/crt0_common.d: $(LIBTRANSISTOR_HOME)/lib/crt0_common.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(LIBTRANSISTOR_HOME)/pthread/ -I$(LIBTRANSISTOR_HOME)/pthread/sys/switch/ $(libtransistor_WARNINGS) -MMD -MP -fno-stack-protector -c -o $(LIBTRANSISTOR_HOME)/build/lib/crt0_common.o $<

$(LIBTRANSISTOR_HOME)/build/lib/%.o $(LIBTRANSISTOR_HOME)/build/lib/%.d: $(LIBTRANSISTOR_HOME)/lib/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(libtransistor_WARNINGS) -MMD -MP -c -o $(LIBTRANSISTOR_HOME)/build/lib/$*.o $<

include $(libtransistor_OBJECT_FILES:.o=.d)

$(LIBTRANSISTOR_HOME)/build/lib/%.o $(LIBTRANSISTOR_HOME)/build/lib/%.d: $(LIBTRANSISTOR_HOME)/lib/%.S
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $(LIBTRANSISTOR_HOME)/build/lib/$*.o
	touch $(LIBTRANSISTOR_HOME)/build/lib/$*.d

# CLEAN RULES

.PHONY: clean_lib clean

clean_lib:
	rm -rf $(LIBTRANSISTOR_HOME)/build/lib/

# add to default target
default: $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nro.a \
	$(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nso.a
