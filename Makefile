include libtransistor.mk

libtransistor_TESTS := malloc bsd_ai_packing bsd sfdnsres nv helloworld hid hexdump args ssp stdin multiple_set_heap_size vi gpu display am sdl audio_output init_fini_arrays ipc_server pthread cpp
libtransistor_OBJECT_NAMES := crt0_common.o svc.o ipc.o tls.o util.o ipc/sm.o ipc/bsd.o ipc/nv.o ipc/hid.o ipc/ro.o ipc/nifm.o hid.o ipc/vi.o display/binder.o display/parcel.o display/surface.o gpu/gpu.o ipc/am.o display/graphic_buffer_queue.o display/display.o gfx/blit.o ipc/time.o syscalls/syscalls.o syscalls/fd.o syscalls/sched.o syscalls/socket.o ipc/audio.o ipc/bpc.o ipcserver.o strtold.o
libtransistor_OBJECT_FILES := $(addprefix $(LIBTRANSISTOR_HOME)/build/lib/,$(libtransistor_OBJECT_NAMES))

pthread_SRCS=	rthread_attr.c rthread_barrier.c rthread_barrier_attr.c rthread_cond.c rthread_condattr.c rthread_debug.c rthread_getcpuclockid.c rthread_internal.c rthread_mutex.c rthread_mutex_prio.c rthread_mutexattr.c rthread_once.c rthread_rwlock.c rthread_rwlockattr.c rthread_sched.c rthread_sem.c rthread_sig.c rthread_spin_lock.c rthread_thread.c rthread_tls.c sched_prio.c sys/switch/phal.c
pthread_OBJECT_FILES := $(addprefix $(LIBTRANSISTOR_HOME)/build/pthread/,$(pthread_SRCS:.c=.o))
pthread_CC_FLAGS := -I$(LIBTRANSISTOR_HOME)/pthread -I$(LIBTRANSISTOR_HOME)/pthread/sys/switch -Wno-incompatible-pointer-types-discards-qualifiers -Wno-unused-variable -Wno-unused-function -Wno-unused-label

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
export RANLIB_FOR_TARGET = $(RANLIB)
export CFLAGS_FOR_TARGET = $(CC_FLAGS) -Wno-unused-command-line-argument -Wno-error-implicit-function-declaration

.SUFFIXES: # disable built-in rules
.SECONDARY: # don't delete intermediate files

.PHONY: clean clean_newlib clean_compiler-rt clean_sdl distclean

all: $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nro.a \
	$(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nso.a \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nro,$(libtransistor_TESTS))) \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nso,$(libtransistor_TESTS))) \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nro.so,$(libtransistor_TESTS))) \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nso.so,$(libtransistor_TESTS)))

run_tests: run_helloworld_test run_hexdump_test run_malloc_test run_bsd_ai_packing_test run_bsd_test run_sfdnsres_test run_multiple_set_heap_size_test run_init_fini_arrays_test run_cpp_test

run_bsd_test: $(LIBTRANSISTOR_HOME)/build/test/test_bsd.nro $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb
	$(RUBY) $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb $(MEPHISTO)

run_sfdnsres_test: $(LIBTRANSISTOR_HOME)/build/test/test_sfdnsres.nro
	$(MEPHISTO) --enable-sockets --load-nro $<

run_ssp_test: $(LIBTRANSISTOR_HOME)/build/test/test_ssp.nro
	$(MEPHISTO) --enable-sockets --load-nro $<

run_%_test: $(LIBTRANSISTOR_HOME)/build/test/test_%.nro
	$(MEPHISTO) --load-nro $<

$(LIBTRANSISTOR_HOME)/build/test/%.o: $(LIBTRANSISTOR_HOME)/test/%.c $(LIBTRANSISTOR_HOME)/build/sdl2_install/lib/libSDL2.a
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/test/%.o: $(LIBTRANSISTOR_HOME)/test/%.cpp $(CXX_LIBS)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

# Disable stack protector for crt0_common
$(LIBTRANSISTOR_HOME)/build/lib/crt0_common.o: $(LIBTRANSISTOR_HOME)/lib/crt0_common.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(LIBTRANSISTOR_HOME)/pthread/ -I$(LIBTRANSISTOR_HOME)/pthread/sys/switch/ $(WARNINGS) -fno-stack-protector -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/lib/%.o: $(LIBTRANSISTOR_HOME)/lib/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/lib/%.o: $(LIBTRANSISTOR_HOME)/lib/%.S
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $@

# Pthread rules
$(LIBTRANSISTOR_HOME)/build/pthread/%.o: $(LIBTRANSISTOR_HOME)/pthread/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(pthread_CC_FLAGS) -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/openlibm/%.o: $(LIBTRANSISTOR_HOME)/openlibm/src/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/test/%.nro.so: $(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(LIBTRANSISTOR_NRO_LDFLAGS)

$(LIBTRANSISTOR_HOME)/build/test/%.nso.so: $(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_NSO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(LIBTRANSISTOR_NSO_LDFLAGS)

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

$(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libm.a $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a: $(LIBTRANSISTOR_HOME)/build/newlib/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/newlib/

$(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a: $(pthread_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

$(LIBTRANSISTOR_HOME)/build/openlibm/libm.a: $(openlibm_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

$(COMPILER_RT_BUILTINS_LIB): $(LIBTRANSISTOR_HOME)/build/compiler-rt/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/compiler-rt/

$(LIBCXX_LIB): $(LIBTRANSISTOR_HOME)/build/libcxx/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/libcxx

$(LIBCXXABI_LIB): $(LIBTRANSISTOR_HOME)/build/libcxxabi/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/libcxxabi

$(LIBUNWIND_LIB): $(LIBTRANSISTOR_HOME)/build/libunwind/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/libunwind

$(LIBTRANSISTOR_HOME)/build/compiler-rt/Makefile:
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(LIBTRANSISTOR_HOME)/compiler-rt \
		-DCOMPILER_RT_BAREMETAL_BUILD=ON \
		-DCOMPILER_RT_BUILD_BUILTINS=ON \
		-DCOMPILER_RT_BUILD_SANITIZERS=OFF \
		-DCOMPILER_RT_BUILD_XRAY=OFF \
		-DCOMPILER_RT_BUILD_XRAY=OFF \
		-DCOMPILER_RT_BUILD_PROFILE=OFF \
		-DCMAKE_C_COMPILER="$(CC)" \
		-DCMAKE_C_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER="$(CXX)" \
		-DCMAKE_CXX_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_CXX_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_AR="$(AR)" \
		-DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" \
		-DCOMPILER_RT_DEFAULT_TARGET_ONLY=ON \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux

$(LIBTRANSISTOR_HOME)/build/libcxx/Makefile: $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a $(COMPILER_RT_BUILTINS_LIB) $(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a $(LIBTRANSISTOR_HOME)/build/openlibm/libm.a
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(LIBTRANSISTOR_HOME)/libcxx \
		-DLIBCXX_ENABLE_SHARED=NO \
		-DLIBCXX_USE_COMPILER_RT=ON \
		-DLIBCXX_CXX_ABI=libcxxabi \
		-DLIBCXX_CXX_ABI_INCLUDE_PATHS=$(LIBTRANSISTOR_HOME)/libcxxabi/include \
		-DLIBCXX_ENABLE_EXPERIMENTAL_LIBRARY=NO \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_CXX_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_CXX_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_AR="$(AR)" \
		-DCMAKE_EXE_LINKER_FLAGS="-Wl,-T$(LIBTRANSISTOR_HOME)/link.T -fuse-ld=lld $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a $(COMPILER_RT_BUILTINS_LIB) $(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a $(LIBTRANSISTOR_HOME)/build/openlibm/libm.a" \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux

$(LIBTRANSISTOR_HOME)/build/libcxxabi/Makefile: $(LIBCXX_LIB)
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(LIBTRANSISTOR_HOME)/libcxxabi \
		-DLIBCXXABI_USE_LLVM_UNWINDER=ON \
		-DLIBCXXABI_ENABLE_STATIC_UNWINDER=ON \
		-DLIBCXXABI_LIBCXX_LIBRARY_PATH="$(LIBTRANSISTOR_HOME)/build/libcxx/lib" \
		-DLIBCXXABI_LIBCXX_INCLUDES="$(LIBTRANSISTOR_HOME)/libcxx/include" \
		-DLIBCXXABI_ENABLE_SHARED=OFF \
		-DLIBCXXABI_BAREMETAL=ON \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_CXX_FLAGS="$(CXX_FLAGS)" \
		-DCMAKE_CXX_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_AR="$(AR)" \
		-DCMAKE_EXE_LINKER_FLAGS="-Wl,-T$(LIBTRANSISTOR_HOME)/link.T -fuse-ld=lld $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a $(COMPILER_RT_BUILTINS_LIB) $(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a" \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux

$(LIBTRANSISTOR_HOME)/build/libunwind/Makefile: $(LIBCXX_LIB)
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(LIBTRANSISTOR_HOME)/libunwind \
		-DLIBUNWIND_ENABLE_SHARED=OFF \
		-DLIBUNWIND_ENABLE_ARM_WMMX=ON \
		-DLIBUNWIND_USE_COMPILER_RT=ON \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS="$(CC_FLAGS) -D_LIBUNWIND_IS_BAREMETAL=1" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_CXX_FLAGS="$(CXX_FLAGS) -D_LIBUNWIND_IS_BAREMETAL=1" \
		-DCMAKE_CXX_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_AR="$(AR)" \
		-DCMAKE_EXE_LINKER_FLAGS="-Wl,-T$(LIBTRANSISTOR_HOME)/link.T -fuse-ld=lld $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a $(COMPILER_RT_BUILTINS_LIB) $(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a" \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux

$(LIBTRANSISTOR_HOME)/build/sdl2_install/lib/libSDL2.a: $(LIBTRANSISTOR_HOME)/build/sdl2/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/sdl2/
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/sdl2/ install

$(LIBTRANSISTOR_HOME)/build/sdl2/Makefile: $(LIBTRANSISTOR_HOME)/build/openlibm/libm.a $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a
	mkdir -p $(@D)
	cd $(@D); $(LIBTRANSISTOR_HOME)/sdl2/configure "CFLAGS=$(CFLAGS)" "CC=$(CC)" "AR=$(AR)" "RANLIB=$(RANLIB)" "LDFLAGS=-L$(LIBTRANSISTOR_HOME)/build/openlibm -L$(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/ -lc -lm" --host=aarch64-none-switch --disable-audio --disable-joystick --disable-power --disable-filesystem --disable-threads --disable-cpuinfo --enable-timers --enable-video --disable-shared --enable-static --prefix=$(LIBTRANSISTOR_HOME)/build/sdl2_install/

clean:
	rm -rf $(LIBTRANSISTOR_HOME)/build/lib/* $(LIBTRANSISTOR_HOME)/build/test/* $(LIBTRANSISTOR_HOME)/docs

clean_pthread:
	rm -fr build/pthread

clean_newlib:
	rm -rf build/newlib

clean_compiler-rt:
	rm -rf build/compiler-rt

clean_sdl:
	rm -rf build/sdl2 build/sdl2_install

distclean: clean clean_newlib clean_compiler-rt clean_pthread clean_sdl
