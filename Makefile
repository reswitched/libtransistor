SOURCE_ROOT := .
BUILD_DIR := $(SOURCE_ROOT)/build/

LIBTRANSISTOR_HOME := $(realpath .)/dist

ifeq ($(shell id -u), 0)
   $(error "This script must not be run as root")
endif

include libtransistor.mk

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

.PHONY: default

default:

include mk/transistor_support.mk
include mk/newlib.mk
include mk/transistor_headers.mk
include mk/pthread.mk
include mk/compiler-rt.mk
include mk/liblzma.mk
include mk/sdl2.mk
include mk/openlibm.mk
include mk/libcxx.mk
include mk/transistor.mk

DIST := $(DIST_TRANSISTOR_HEADERS) $(DIST_PTHREAD_HEADERS) $(DIST_PTHREAD) $(DIST_NEWLIB) $(DIST_COMPILER_RT) $(DIST_LIBLZMA) $(DIST_OPENLIBM) $(DIST_LIBCXX) $(DIST_LIBCXXABI) $(DIST_LIBUNWIND) $(DIST_TRANSISTOR) $(DIST_SDL2)

include mk/tests.mk

dist: $(DIST)
.PHONY: dist

default: $(DIST)

clean: clean_transistor clean_test
	rm -rf $(SOURCE_ROOT)/docs

distclean:
	rm -rf $(BUILD_DIR)
	rm -rf $(LIBTRANSISTOR_HOME)
