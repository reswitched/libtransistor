ifeq ($(LIBTRANSISTOR_HOME),)
    LIBTRANSISTOR_HOME := $(realpath ./)
else
    LIBTRANSISTOR_HOME := $(realpath $(LIBTRANSISTOR_HOME))
endif

SYS_INCLUDES := -isystem $(LIBTRANSISTOR_HOME)/newlib/newlib/libc/sys/switch/include/ -isystem $(LIBTRANSISTOR_HOME)/newlib/newlib/libc/sys/switch/ -isystem $(LIBTRANSISTOR_HOME)/newlib/newlib/libc/include/
INCLUDES := $(SYS_INCLUDES) -I$(LIBTRANSISTOR_HOME)/include/ -I$(LIBTRANSISTOR_HOME)/libssp/include
WARNINGS := -Wall -Wextra -Wno-unused-parameter

LD := ld.lld$(LLVM_POSTFIX)
CC := clang$(LLVM_POSTFIX)
CXX := clang++$(LLVM_POSTFIX)
AS := llvm-mc$(LLVM_POSTFIX)
AR := llvm-ar$(LLVM_POSTFIX)
LD_FLAGS := -Bsymbolic --shared --emit-relocs --no-gc-sections --no-undefined -T $(LIBTRANSISTOR_HOME)/link.T -L $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/ -L $(LIBTRANSISTOR_HOME)/libssp/ -L $(LIBTRANSISTOR_HOME)/build/compiler-rt/lib/linux/
CC_FLAGS := -g -fPIC -ffreestanding -fexceptions -O0 -mtune=cortex-a53 -target aarch64-none-linux-gnu -nostdlib -nostdlibinc $(INCLUDES) $(WARNINGS)
AR_FLAGS := rcs
# for compatiblity
CFLAGS := $(CC_FLAGS)
AS_FLAGS := -arch=aarch64 -triple aarch64-none-switch
PYTHON2 := python2
MEPHISTO := ctu
RUBY := ruby
COMPILER_RT_BUILTINS_LIB := $(LIBTRANSISTOR_HOME)/build/compiler-rt/lib/linux/libclang_rt.builtins-aarch64.a
LIBTRANSISTOR_COMMON_LIBS := $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a $(LIBTRANSISTOR_HOME)/libssp/libssp.a $(COMPILER_RT_BUILTINS_LIB)
LIBTRANSISTOR_NRO_LIB := $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nro.a
LIBTRANSISTOR_NSO_LIB := $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nso.a
LIBTRANSISTOR_NRO_LDFLAGS := --whole-archive $(LIBTRANSISTOR_NRO_LIB) --no-whole-archive $(LIBTRANSISTOR_COMMON_LIBS)
LIBTRANSISTOR_NSO_LDFLAGS := --whole-archive $(LIBTRANSISTOR_NSO_LIB) --no-whole-archive $(LIBTRANSISTOR_COMMON_LIBS)

%.nro: %.nro.so
	$(PYTHON2) $(LIBTRANSISTOR_HOME)/tools/elf2nxo.py $< $@ nro

%.nso: %.nso.so
	$(PYTHON2) $(LIBTRANSISTOR_HOME)/tools/elf2nxo.py $< $@ nso
