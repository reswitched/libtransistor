LIBTRANSISTOR_HOME=./

include libtransistor.mk

libtransistor_TESTS := malloc bsd_ai_packing bsd sfdnsres nv helloworld hid
libtransistor_OBJECT_NAMES := svc.o ipc.o tls.o util.o ipc/sm.o ipc/bsd.o ipc/nv.o ipc/hid.o ipc/ro.o hid.o
libtransistor_OBJECT_FILES := $(addprefix $(LIBTRANSISTOR_HOME)/build/lib/,$(libtransistor_OBJECT_NAMES))

# for building newlib
export AR_FOR_TARGET = llvm-ar$(LLVM_POSTFIX)
export AS_FOR_TARGET = llvm-mc$(LLVM_POSTFIX) -arch=aarch64 -mattr=+neon
export LD_FOR_TARGET = ld.lld$(LLVM_POSTFIX)
export RANLIB_FOR_TARGET = llvm-ranlib$(LLVM_POSTFIX)
export CC_FOR_TARGET = clang$(LLVM_POSTFIX) -g -fPIC -ffreestanding -fexceptions -target aarch64-none-linux-gnu -O0 -mtune=cortex-a53 -ccc-gcc-name aarch64-switch-gcc -Wno-unused-command-line-argument

.SUFFIXES: # disable built-in rules

all: $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nro.a $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nso.a $(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nro,$(libtransistor_TESTS))) $(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nso,$(libtransistor_TESTS))) $(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nro.so,$(libtransistor_TESTS))) $(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nso.so,$(libtransistor_TESTS)))

run_tests: run_helloworld_test run_malloc_test run_bsd_ai_packing_test run_bsd_test run_sfdnsres_test

run_bsd_test: $(LIBTRANSISTOR_HOME)/build/test/test_bsd.nro $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb
	$(RUBY) $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb $(MEPHISTO)

run_sfdnsres_test: $(LIBTRANSISTOR_HOME)/build/test/test_sfdnsres.nro
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

clean:
	rm -rf $(LIBTRANSISTOR_HOME)/build/lib/* $(LIBTRANSISTOR_HOME)/build/test/*
