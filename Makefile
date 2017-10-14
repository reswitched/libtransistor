LD := ld.lld
CC := clang
AS := llvm-mc
LD_FLAGS := -Bsymbolic --shared --emit-relocs --no-gc-sections --no-undefined -T link.T
CC_FLAGS := -g -fPIC -ffreestanding -fexceptions -target aarch64-none-linux-gnu -O0 -mtune=cortex-a53 -I include/ -I newlib/newlib/libc/include/ -I newlib/newlib/libc/sys/switch/include/
AS_FLAGS := -arch=aarch64 -triple aarch64-none-switch
PYTHON2 := python2
MEPHISTO := ctu
RUBY := ruby

libtransistor_TESTS := malloc bsd_ai_packing bsd sfdnsres

libtransistor_OBJECTS := build/lib/svc.o build/lib/ipc.o build/lib/tls.o build/lib/util.o build/lib/ipc/sm.o build/lib/ipc/bsd.o

# for building newlib
export AR_FOR_TARGET = llvm-ar
export AS_FOR_TARGET = llvm-mc -arch=aarch64 -mattr=+neon
export LD_FOR_TARGET = ld.lld
export RANLIB_FOR_TARGET = llvm-ranlib
export CC_FOR_TARGET = clang -g -fPIC -ffreestanding -fexceptions -target aarch64-none-linux-gnu -O0 -mtune=cortex-a53 -ccc-gcc-name aarch64-switch-gcc -Wno-unused-command-line-argument

.SUFFIXES: # disable built-in rules

all: build/lib/libtransistor.nro.a build/lib/libtransistor.nso.a $(addprefix build/test/test_,$(addsuffix .nro,$(libtransistor_TESTS))) $(addprefix build/test/test_,$(addsuffix .nso,$(libtransistor_TESTS))) $(addprefix build/test/test_,$(addsuffix .nro.so,$(libtransistor_TESTS))) $(addprefix build/test/test_,$(addsuffix .nso.so,$(libtransistor_TESTS)))

run_tests: run_malloc_test run_bsd_ai_packing_test run_bsd_test run_sfdnsres_test

run_bsd_test: build/test/test_bsd.nro test_helpers/bsd.rb
	$(RUBY) test_helpers/bsd.rb $(MEPHISTO)

run_sfdnsres_test: build/test/test_sfdnsres.nro
	$(MEPHISTO) --enable-sockets --load-nro $<

run_%_test: build/test/test_%.nro
	$(MEPHISTO) --load-nro $<

build/test/%.o: test/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -o $@ $<

build/lib/%.o: lib/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -o $@ $<

build/lib/%.o: lib/%.S
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $@

build/test/%.nro: build/test/%.nro.so
	mkdir -p $(@D)
	$(PYTHON2) ./tools/elf2nxo.py $< $@ nro

build/test/%.nso: build/test/%.nso.so
	mkdir -p $(@D)
	$(PYTHON2) ./tools/elf2nxo.py $< $@ nso

build/test/%.nro.so: build/test/%.o build/lib/libtransistor.nro.a newlib/aarch64-none-switch/newlib/libc.a 
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< --whole-archive build/lib/libtransistor.nro.a --no-whole-archive newlib/aarch64-none-switch/newlib/libc.a

build/test/%.nso.so: build/test/%.o build/lib/libtransistor.nso.a newlib/aarch64-none-switch/newlib/libc.a 
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< --whole-archive build/lib/libtransistor.nso.a --no-whole-archive newlib/aarch64-none-switch/newlib/libc.a

build/lib/libtransistor.nro.a: build/lib/crt0.nro.o $(libtransistor_OBJECTS)
	mkdir -p $(@D)
	rm -f $@
	ar rcs $@ $+

build/lib/libtransistor.nso.a: build/lib/crt0.nso.o $(libtransistor_OBJECTS)
	mkdir -p $(@D)
	rm -f $@
	ar rcs $@ $+

newlib/Makefile:
	cd newlib; ./configure --target=aarch64-none-switch --without-rdimon

newlib/aarch64-none-switch/newlib/libc.a: newlib/Makefile
	make -C newlib/

newlib/aarch64-none-switch/libgloss/libnosys/libnosys.a: newlib/aarch64-none-switch/newlib/libc.a
newlib/aarch64-none-switch/libgloss/aarch64/librdimon.a: newlib/aarch64-none-switch/newlib/libc.a

clean:
	rm -rf build/lib/* build/test/*
