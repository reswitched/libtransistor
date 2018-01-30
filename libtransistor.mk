ifeq ($(LIBTRANSISTOR_HOME),)
    LIBTRANSISTOR_HOME := $(realpath ./)
else
    LIBTRANSISTOR_HOME := $(realpath $(LIBTRANSISTOR_HOME))
endif

# llvm programs
LLVM_CONFIG := llvm-config$(LLVM_POSTFIX)
LLVM_BINDIR := $(shell $(LLVM_CONFIG) --bindir)
LD := $(LLVM_BINDIR)/ld.lld
CC := $(LLVM_BINDIR)/clang
CXX := $(LLVM_BINDIR)/clang++
AS := $(LLVM_BINDIR)/llvm-mc
AR := $(LLVM_BINDIR)/llvm-ar
RANLIB := $(LLVM_BINDIR)/llvm-ranlib

# interpreters
PYTHON3 := python3
MEPHISTO := ctu
RUBY := ruby

SYS_INCLUDES := -isystem $(LIBTRANSISTOR_HOME)/pthread/include \
	-isystem $(LIBTRANSISTOR_HOME)/newlib/newlib/libc/sys/switch/include/ \
	-isystem $(LIBTRANSISTOR_HOME)/newlib/newlib/libc/sys/switch/ \
	-isystem $(LIBTRANSISTOR_HOME)/newlib/newlib/libc/include/ \
	-isystem $(LIBTRANSISTOR_HOME)/xz/src/liblzma/api/

INCLUDES := $(SYS_INCLUDES) -I$(LIBTRANSISTOR_HOME)/include/ -I $(LIBTRANSISTOR_HOME)/build/sdl2_install/include/

LD_FLAGS := -Bsymbolic --shared --no-gc-sections --no-undefined -T $(LIBTRANSISTOR_HOME)/link.T \
	-L $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/ \
	-L $(LIBTRANSISTOR_HOME)/build/compiler-rt/lib/linux/ \
	-L $(LIBTRANSISTOR_HOME)/build/sdl2_install/lib/ \
	-L $(LIBTRANSISTOR_HOME)/build/pthread/ \
	-L $(LIBTRANSISTOR_HOME)/build/xz/src/liblzma/.libs/ \
	-L $(LIBTRANSISTOR_HOME)/build/lib/

CC_FLAGS := -g -fPIC -ffreestanding -fexceptions -fuse-ld=lld -fstack-protector-strong -O3 -mtune=cortex-a53 -target aarch64-none-linux-gnu -nostdlib -nostdlibinc $(INCLUDES) -D__SWITCH__=1 -Wno-unused-command-line-argument
AR_FLAGS := rcs
AS_FLAGS := -arch=aarch64 -triple aarch64-none-switch

# for compatiblity
CFLAGS := $(CC_FLAGS)

LIB_DEP_COMPILER_RT_BUILTINS := $(LIBTRANSISTOR_HOME)/build/compiler-rt/lib/linux/libclang_rt.builtins-aarch64.a
LIB_DEP_SDL2 := $(LIBTRANSISTOR_HOME)/build/sdl2_install/lib/libSDL2.a
LIB_DEP_NEWLIB_LIBC := $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a
LIB_DEP_NEWLIB_LIBM := $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libm.a
LIB_DEP_PTHREAD := $(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a
LIB_DEP_LIBLZMA := $(LIBTRANSISTOR_HOME)/build/xz/src/liblzma/.libs/liblzma.a
LIBTRANSISTOR_COMMON_LIB_DEPS := $(LIB_DEP_NEWLIB_LIBC) $(LIB_DEP_NEWLIB_LIBM) $(LIB_DEP_COMPILER_RT_BUILTINS) $(LIB_DEP_SDL2) $(LIB_DEP_PTHREAD) $(LIB_DEP_LIBLZMA)
LIBTRANSISTOR_COMMON_LIBS := $(LIBTRANSISTOR_COMMON_LIB_DEPS) # for older Makefiles
LIBTRANSISTOR_NRO_DEP := $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nro.a
LIBTRANSISTOR_NSO_DEP := $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nso.a
LIBTRANSISTOR_NRO_LIB := $(LIBTRANSISTOR_NRO_DEP)
LIBTRANSISTOR_NSO_LIB := $(LIBTRANSISTOR_NSO_DEP)
LIBTRANSISTOR_NRO_DEPS := $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nro.a $(LIBTRANSISTOR_COMMON_LIB_DEPS)
LIBTRANSISTOR_NSO_DEPS := $(LIBTRANSISTOR_HOME)/build/lib/libtransistor.nso.a $(LIBTRANSISTOR_COMMON_LIB_DEPS)

LIBTRANSISTOR_COMMON_LDFLAGS := -lc -lm -lclang_rt.builtins-aarch64 -lSDL2 -lpthread -llzma

LIBTRANSISTOR_NRO_LDFLAGS := --whole-archive -ltransistor.nro --no-whole-archive $(LIBTRANSISTOR_COMMON_LDFLAGS)
LIBTRANSISTOR_NSO_LDFLAGS := --whole-archive -ltransistor.nso --no-whole-archive $(LIBTRANSISTOR_COMMON_LDFLAGS)

%.nro: %.nro.so
	$(PYTHON3) $(LIBTRANSISTOR_HOME)/tools/elf2nxo.py $< $@ nro

%.nso: %.nso.so
	$(PYTHON3) $(LIBTRANSISTOR_HOME)/tools/elf2nxo.py $< $@ nso
