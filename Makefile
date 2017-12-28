include libtransistor.mk

libtransistor_TESTS := malloc bsd_ai_packing bsd sfdnsres nv helloworld hid hexdump args ssp stdin multiple_set_heap_size vi gpu display am sdl sqfs_img audio_output
libtransistor_OBJECT_NAMES := crt0_common.o svc.o ipc.o tls.o util.o ipc/sm.o ipc/bsd.o ipc/nv.o ipc/hid.o ipc/ro.o ipc/nifm.o hid.o context.o ipc/vi.o display/binder.o display/parcel.o display/surface.o gpu/gpu.o ipc/am.o display/graphic_buffer_queue.o display/display.o gfx/blit.o ipc/time.o syscalls/syscalls.o syscalls/fd.o syscalls/sched.o syscalls/socket.o lz4.o squashfs/cache.o squashfs/decompress.o squashfs/dir.o squashfs/file.o squashfs/fs.o squashfs/hash.o squashfs/nonstd-pread.o squashfs/nonstd-stat.o squashfs/stack.o squashfs/swap.o squashfs/table.o squashfs/traverse.o squashfs/util.o squashfs/xattr.o fs/blobfd.o fs/squashfs.o fs/fs.o ipc/audio.o ipc/bpc.o
libtransistor_OBJECT_FILES := $(addprefix $(LIBTRANSISTOR_HOME)/build/lib/,$(libtransistor_OBJECT_NAMES))

# for building newlib and sdl
export LD
export CC
export CXX
export AS
export AR
export LD_FOR_TARGET = $(LD)
export CC_FOR_TARGET = $(CC)
export AS_FOR_TARGET = $(AS) -arch=aarch64 -mattr=+neon
export AR_FOR_TARGET = $(AR)
export RANLIB_FOR_TARGET = llvm-ranlib$(LLVM_POSTFIX)
export CFLAGS_FOR_TARGET = $(CC_FLAGS) -Wno-unused-command-line-argument

.SUFFIXES: # disable built-in rules

.PHONY: clean, clean_newlib, clean_compiler-rt, distclean

all: $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nro.a \
	$(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nso.a \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nro,$(libtransistor_TESTS))) \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nso,$(libtransistor_TESTS))) \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nro.so,$(libtransistor_TESTS))) \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nso.so,$(libtransistor_TESTS)))

run_tests: run_helloworld_test run_hexdump_test run_malloc_test run_bsd_ai_packing_test run_bsd_test run_sfdnsres_test run_multiple_set_heap_size_test

run_bsd_test: $(LIBTRANSISTOR_HOME)/build/test/test_bsd.nro $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb
	$(RUBY) $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb $(MEPHISTO)

run_sfdnsres_test: $(LIBTRANSISTOR_HOME)/build/test/test_sfdnsres.nro
	$(MEPHISTO) --enable-sockets --load-nro $<

run_ssp_test: $(LIBTRANSISTOR_HOME)/build/test/test_ssp.nro
	$(MEPHISTO) --enable-sockets --load-nro $<

run_%_test: $(LIBTRANSISTOR_HOME)/build/test/test_%.nro
	$(MEPHISTO) --load-nro $<

.SECONDARY:

$(LIBTRANSISTOR_HOME)/build/test/%.o: $(LIBTRANSISTOR_HOME)/test/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(WARNINGS) -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/test/%.squashfs.o: $(LIBTRANSISTOR_HOME)/build/test/%.squashfs
	mkdir -p $(@D)
	$(LD) -s -r -b binary -m aarch64elf -T $(LIBTRANSISTOR_HOME)/fs.T -o $@ $<

$(LIBTRANSISTOR_HOME)/build/empty_file:
	touch $@

$(LIBTRANSISTOR_HOME)/build/test/%.squashfs: $(LIBTRANSISTOR_HOME)/test/fs_%/*
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp lz4 -nopad -noappend

$(LIBTRANSISTOR_HOME)/build/test/%.squashfs: $(LIBTRANSISTOR_HOME)/build/empty_file
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp lz4 -nopad -noappend

# Disable stack protector for crt0_common
$(LIBTRANSISTOR_HOME)/build/lib/crt0_common.o: $(LIBTRANSISTOR_HOME)/lib/crt0_common.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(WARNINGS) -fno-stack-protector -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/lib/%.o: $(LIBTRANSISTOR_HOME)/lib/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(WARNINGS) -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/lib/%.o: $(LIBTRANSISTOR_HOME)/lib/%.S
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $@

$(LIBTRANSISTOR_HOME)/build/test/%.nro.so: $(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_HOME)/build/test/%.squashfs.o $(LIBTRANSISTOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(LIBTRANSISTOR_HOME)/build/test/$*.squashfs.o $(LIBTRANSISTOR_NRO_LDFLAGS) -lm

$(LIBTRANSISTOR_HOME)/build/test/%.nso.so: $(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_HOME)/build/test/%.squashfs.o $(LIBTRANSISTOR_NSO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(LIBTRANSISTOR_HOME)/build/test/$*.squashfs.o $(LIBTRANSISTOR_NSO_LDFLAGS) -lm

$(LIBTRANSISTOR_NRO_LIB): $(LIBTRANSISTOR_HOME)/build/lib/crt0.nro.o $(libtransistor_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

$(LIBTRANSISTOR_NSO_LIB): $(LIBTRANSISTOR_HOME)/build/lib/crt0.nso.o $(libtransistor_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

$(LIBTRANSISTOR_HOME)/build/newlib/Makefile:
	mkdir -p $(@D)
	cd $(@D); $(LIBTRANSISTOR_HOME)/newlib/configure --disable-multilib --target=aarch64-none-switch --without-rdimon

$(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a: $(LIBTRANSISTOR_HOME)/build/newlib/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/newlib/

$(LIBTRANSISTOR_HOME)/libssp/libssp.a:
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/libssp

$(COMPILER_RT_BUILTINS_LIB): $(LIBTRANSISTOR_HOME)/build/compiler-rt/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/compiler-rt/

$(LIBTRANSISTOR_HOME)/build/compiler-rt/Makefile:
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(LIBTRANSISTOR_HOME)/compiler-rt \
		-DCOMPILER_RT_BAREMETAL_BUILD=ON \
		-DCOMPILER_RT_BUILD_BUILTINS=ON \
		-DCOMPILER_RT_BUILD_SANITIZERS=OFF \
		-DCOMPILER_RT_BUILD_XRAY=OFF \
		-DCOMPILER_RT_BUILD_XRAY=OFF \
		-DCOMPILER_RT_BUILD_PROFILE=OFF \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" \
		-DCOMPILER_RT_DEFAULT_TARGET_ONLY=ON \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX)

$(LIBTRANSISTOR_HOME)/build/sdl2_install/lib/libSDL2.a: $(LIBTRANSISTOR_HOME)/build/sdl2/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/sdl2/
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/sdl2/ install

$(LIBTRANSISTOR_HOME)/build/sdl2/Makefile:
	mkdir -p $(@D)
	cd $(@D); $(LIBTRANSISTOR_HOME)/sdl2/configure "CFLAGS=$(CFLAGS)" --host=aarch64-none-switch --disable-audio --disable-joystick --disable-power --disable-filesystem --disable-threads --enable-timers --enable-video --prefix=$(LIBTRANSISTOR_HOME)/build/sdl2_install/

clean:
	rm -rf $(LIBTRANSISTOR_HOME)/build/lib/* $(LIBTRANSISTOR_HOME)/build/test/*
	$(MAKE) -C libssp clean

clean_newlib:
	rm -rf build/newlib

clean_compiler-rt:
	rm -rf build/compiler-rt

distclean: clean clean_newlib clean_compiler-rt
