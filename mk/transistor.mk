# LIBTRANSISTOR

libtransistor_OBJECT_NAMES := crt0_common.o svc.o ipc.o tls.o util.o ipc/sm.o ipc/bsd.o ipc/nv.o ipc/hid.o ipc/ro.o ipc/nifm.o hid.o ipc/vi.o display/binder.o display/parcel.o display/surface.o gpu/gpu.o ipc/am.o display/graphic_buffer_queue.o display/display.o gfx/blit.o ipc/time.o syscalls/syscalls.o syscalls/fd.o syscalls/sched.o syscalls/socket.o lz4.o squashfs/cache.o squashfs/decompress.o squashfs/dir.o squashfs/file.o squashfs/fs.o squashfs/hash.o squashfs/nonstd-pread.o squashfs/nonstd-stat.o squashfs/stack.o squashfs/swap.o squashfs/table.o squashfs/traverse.o squashfs/util.o squashfs/xattr.o fs/blobfd.o fs/squashfs.o fs/fs.o ipc/audio.o ipc/bpc.o ipcserver.o strtold.o ipc/pm.o alloc_pages.o
libtransistor_OBJECT_FILES := $(addprefix $(BUILD_DIR)/transistor/,$(libtransistor_OBJECT_NAMES))

libtransistor_WARNINGS := -Wall -Wextra -Werror-implicit-function-declaration -Wno-unused-parameter -Wno-unused-command-line-argument

libtransistor_BUILD_DEPS := $(DIST_NEWLIB) $(DIST_PTHREAD_HEADERS) $(DIST_PTHREAD) $(DIST_LIBLZMA) $(DIST_TRANSISTOR_HEADERS) $(DIST_TRANSISTOR_SUPPORT)

# ARCHIVE RULES

libtransistor_TARGET_NRO := $(BUILD_DIR)/transistor/libtransistor.nro.a
libtransistor_TARGET_NSO := $(BUILD_DIR)/transistor/libtransistor.nso.a

$(libtransistor_TARGET_NRO): $(BUILD_DIR)/transistor/crt0.nro.o $(libtransistor_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

$(libtransistor_TARGET_NSO): $(BUILD_DIR)/transistor/crt0.nso.o $(libtransistor_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

# BUILD RULES

# Disable stack protector for crt0_common
$(BUILD_DIR)/transistor/crt0_common.o $(BUILD_DIR)/transistor/crt0_common.d: $(SOURCE_ROOT)/lib/crt0_common.c $(libtransistor_BUILD_DEPS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(SOURCE_ROOT)/pthread/ -I$(SOURCE_ROOT)/pthread/sys/switch/ $(libtransistor_WARNINGS) -MMD -MP -fno-stack-protector -c -o $(BUILD_DIR)/transistor/crt0_common.o $<

$(BUILD_DIR)/transistor/%.o $(BUILD_DIR)/transistor/%.d: $(SOURCE_ROOT)/lib/%.c $(libtransistor_BUILD_DEPS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(libtransistor_WARNINGS) -MMD -MP -c -o $(BUILD_DIR)/transistor/$*.o $<

#include $(libtransistor_OBJECT_FILES:.o=.d)

$(BUILD_DIR)/transistor/%.o $(BUILD_DIR)/transistor/%.d: $(SOURCE_ROOT)/lib/%.S $(libtransistor_BUILD_DEPS)
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $(BUILD_DIR)/transistor/$*.o
	touch $(BUILD_DIR)/transistor/$*.d

# DIST RULES

DIST_TRANSISTOR := $(DIST_TRANSISTOR_HEADERS) $(DIST_TRANSISTOR_SUPPORT) \
	$(LIBTRANSISTOR_HOME)/lib/libtransistor.nro.a \
	$(LIBTRANSISTOR_HOME)/lib/libtransistor.nso.a \

$(LIBTRANSISTOR_HOME)/lib/libtransistor.nro.a: $(libtransistor_TARGET_NRO)
	install -d $(@D)
	install $< $@

$(LIBTRANSISTOR_HOME)/lib/libtransistor.nso.a: $(libtransistor_TARGET_NSO)
	install -d $(@D)
	install $< $@

.PHONY: dist_transistor
dist_transistor: $(DIST_TRANSISTOR)

# CLEAN RULES

.PHONY: clean_transistor clean

clean_transistor:
	rm -rf $(BUILD_DIR)/transistor/
	rm -rf $(LIBTRANSISTOR_HOME)/lib/libtransistor.nro.a
	rm -rf $(LIBTRANSISTOR_HOME)/lib/libtransistor.nso.a

# add to default target
default: $(LIBTRANSISTOR_HOME)/lib/libtransistor.nro.a \
	$(LIBTRANSISTOR_HOME)/lib/libtransistor.nso.a
