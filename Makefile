SOURCE_ROOT := .
BUILD_DIR := $(SOURCE_ROOT)/build/

LIBTRANSISTOR_HOME := $(realpath .)/dist

ifeq ($(shell id -u), 0)
   $(error "This script must not be run as root")
endif

include $(LIBTRANSISTOR_HOME)/libtransistor.mk

.SUFFIXES: # disable built-in rules
.SECONDARY: # don't delete intermediate files

.PHONY: default

default:

include mk/transistor_headers.mk
include mk/transistor.mk

DIST := $(DIST_TRANSISTOR_HEADERS) $(DIST_TRANSISTOR)

include mk/tests.mk

dist: $(DIST)
.PHONY: dist

default: $(DIST)

clean: clean_transistor clean_test
	rm -rf $(SOURCE_ROOT)/docs

distclean:
	rm -rf $(BUILD_DIR)
	rm -rf $(LIBTRANSISTOR_HOME)
