# Pull target toolchain, otherwise use native system toolchain
ifneq ($(AR_FOR_TARGET),)
AR := $(AR_FOR_TARGET)
endif

ifneq ($(CC_FOR_TARGET),)
CC := $(CC_FOR_TARGET)
endif

ifneq ($(CFLAGS_FOR_TARGET),)
CFLAGS := $(CFLAGS_FOR_TARGET)
endif

.SUFFIXES: # disable built-in rules

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo [CC] $@

all: libssp.a

libssp.a: ssp.o
	@$(AR) rcs $@ $<
	@echo [AR] $@

.PHONY: clean
clean:
	rm -rf *.a *.o
