ifeq ($(LIBTRANSISTOR_HOME),)
    LIBTRANSISTOR_HOME := $(realpath ./)
else
    LIBTRANSISTOR_HOME := $(realpath $(LIBTRANSISTOR_HOME))
endif

LD := ld.lld$(LLVM_POSTFIX)
CC := clang$(LLVM_POSTFIX)
CXX := clang++$(LLVM_POSTFIX)
AS := llvm-mc$(LLVM_POSTFIX)
LD_FLAGS := -Bsymbolic --shared --emit-relocs --no-gc-sections --no-undefined -T $(LIBTRANSISTOR_HOME)/link.T
CC_FLAGS := -g -fPIC -ffreestanding -fexceptions -target aarch64-none-linux-gnu -O0 -mtune=cortex-a53 -I "$(LIBTRANSISTOR_HOME)/include/" -isystem "$(LIBTRANSISTOR_HOME)/newlib/newlib/libc/include/" -isystem "$(LIBTRANSISTOR_HOME)/newlib/newlib/libc/sys/switch/include/" -I$(LIBTRANSISTOR_HOME)/libssp/include -Weverything -Wno-missing-prototypes -Wno-strict-prototypes -Wno-sign-conversion -Wno-missing-variable-declarations -Wno-unused-parameter -Wno-cast-align -Wno-padded -Wno-cast-qual -Wno-gnu-binary-literal -Werror-implicit-function-declaration -Wno-format-pedantic
CFLAGS := $(CC_FLAGS) # for compatiblity
AS_FLAGS := -arch=aarch64 -triple aarch64-none-switch
PYTHON2 := python2
MEPHISTO := ctu
RUBY := ruby
COMPILER_RT_BUILTINS_LIB := $(LIBTRANSISTOR_HOME)/build/compiler-rt/lib/linux/libclang_rt.builtins-aarch64.a
LIBTRANSISTOR_COMMON_LIBS := $(LIBTRANSISTOR_HOME)/newlib/aarch64-none-switch/newlib/libc.a $(LIBTRANSISTOR_HOME)/libssp/libssp.a $(COMPILER_RT_BUILTINS_LIB)
LIBTRANSISTOR_NRO_LIB := $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nro.a
LIBTRANSISTOR_NSO_LIB := $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nso.a
LIBTRANSISTOR_NRO_LDFLAGS := --whole-archive $(LIBTRANSISTOR_NRO_LIB) --no-whole-archive $(LIBTRANSISTOR_COMMON_LIBS)
LIBTRANSISTOR_NSO_LDFLAGS := --whole-archive $(LIBTRANSISTOR_NSO_LIB) --no-whole-archive $(LIBTRANSISTOR_COMMON_LIBS)

%.nro: %.nro.so
	$(PYTHON2) $(LIBTRANSISTOR_HOME)/tools/elf2nxo.py $< $@ nro

%.nso: %.nso.so
	$(PYTHON2) $(LIBTRANSISTOR_HOME)/tools/elf2nxo.py $< $@ nso
