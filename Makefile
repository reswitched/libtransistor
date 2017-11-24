include libtransistor.mk

libtransistor_TESTS := malloc bsd_ai_packing bsd sfdnsres nv helloworld hid hexdump args ssp stdin
libtransistor_OBJECT_NAMES := crt0_common.o svc.o ipc.o tls.o util.o ipc/sm.o ipc/bsd.o ipc/nv.o ipc/hid.o ipc/ro.o ipc/nifm.o hid.o context.o
libtransistor_OBJECT_FILES := $(addprefix $(LIBTRANSISTOR_HOME)/build/lib/,$(libtransistor_OBJECT_NAMES))

# for building newlib
export AR_FOR_TARGET = llvm-ar$(LLVM_POSTFIX)
export AS_FOR_TARGET = llvm-mc$(LLVM_POSTFIX) -arch=aarch64 -mattr=+neon
export LD_FOR_TARGET = ld.lld$(LLVM_POSTFIX)
export RANLIB_FOR_TARGET = llvm-ranlib$(LLVM_POSTFIX)
export CC_FOR_TARGET = clang$(LLVM_POSTFIX) -g -fPIC -ffreestanding -fexceptions -target aarch64-none-linux-gnu -O0 -mtune=cortex-a53 -ccc-gcc-name aarch64-switch-gcc -Wno-unused-command-line-argument -isystem $(realpath $(LIBTRANSISTOR_HOME))/include/
export CC_FLAGS_FOR_TARGET = $(CC_FLAGS)

.SUFFIXES: # disable built-in rules

all: $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nro.a $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nso.a $(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nro,$(libtransistor_TESTS))) $(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nso,$(libtransistor_TESTS))) $(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nro.so,$(libtransistor_TESTS))) $(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nso.so,$(libtransistor_TESTS)))

run_tests: run_helloworld_test run_hexdump_test run_malloc_test run_bsd_ai_packing_test run_bsd_test run_sfdnsres_test

run_bsd_test: $(LIBTRANSISTOR_HOME)/build/test/test_bsd.nro $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb
	$(RUBY) $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb $(MEPHISTO)

run_sfdnsres_test: $(LIBTRANSISTOR_HOME)/build/test/test_sfdnsres.nro
	$(MEPHISTO) --enable-sockets --load-nro $<

run_ssp_test: $(LIBTRANSISTOR_HOME)/build/test/test_ssp.nro
	$(MEPHISTO) --enable-sockets --load-nro $<

run_%_test: $(LIBTRANSISTOR_HOME)/build/test/test_%.nro
	$(MEPHISTO) --load-nro $<

$(LIBTRANSISTOR_HOME)/build/test/%.o: $(LIBTRANSISTOR_HOME)/test/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/lib/%.o: $(LIBTRANSISTOR_HOME)/lib/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(LIBTRANSISTOR_HOME)/build/lib/%.o: $(LIBTRANSISTOR_HOME)/lib/%.S
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $@

$(LIBTRANSISTOR_HOME)/build/test/%.nro.so: $(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(LIBTRANSISTOR_NRO_LDFLAGS)

$(LIBTRANSISTOR_HOME)/build/test/%.nso.so: $(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_NSO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(LIBTRANSISTOR_NSO_LDFLAGS)

$(LIBTRANSISTOR_NRO_LIB): $(LIBTRANSISTOR_HOME)/build/lib/crt0.nro.o $(libtransistor_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	ar rcs $@ $+

$(LIBTRANSISTOR_NSO_LIB): $(LIBTRANSISTOR_HOME)/build/lib/crt0.nso.o $(libtransistor_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	ar rcs $@ $+

$(LIBTRANSISTOR_HOME)/newlib/Makefile:
	cd $(LIBTRANSISTOR_HOME)/newlib; ./configure --target=aarch64-none-switch --without-rdimon

$(LIBTRANSISTOR_HOME)/newlib/aarch64-none-switch/newlib/libc.a: $(LIBTRANSISTOR_HOME)/newlib/Makefile
	make -C $(LIBTRANSISTOR_HOME)/newlib/

$(LIBTRANSISTOR_HOME)/libssp/libssp.a:
	make -C $(LIBTRANSISTOR_HOME)/libssp

$(COMPILER_RT_BUILTINS_LIB): $(LIBTRANSISTOR_HOME)/build/compiler-rt/Makefile
	make -C $(LIBTRANSISTOR_HOME)/build/compiler-rt/

$(LIBTRANSISTOR_HOME)/build/compiler-rt/Makefile:
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(LIBTRANSISTOR_HOME)/compiler-rt -DCOMPILER_RT_BUILD_BUILTINS=ON -DCOMPILER_RT_BUILD_SANITIZERS=OFF -DCOMPILER_RT_BUILD_XRAY=OFF -DCOMPILER_RT_BUILD_XRAY=OFF -DCOMPILER_RT_BUILD_PROFILE=OFF -DCMAKE_C_COMPILER=$(CC) -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" -DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" -DCOMPILER_RT_DEFAULT_TARGET_ONLY=ON -DCMAKE_C_FLAGS="-g -fPIC -fno-stack-protector -ffreestanding -fexceptions -O0 -mtune=cortex-a53 -nostdlib" -DCMAKE_CXX_COMPILER=$(CCPP)

.PHONY: clean
clean:
	rm -rf $(LIBTRANSISTOR_HOME)/build/lib/* $(LIBTRANSISTOR_HOME)/build/test/*
	make -C libssp clean

.PHONY: clean_newlib
clean_newlib:
	make -C newlib clean
	rm -rf newlib/aarch64-none-switch
