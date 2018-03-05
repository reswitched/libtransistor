# NEWLIB

$(BUILD_DIR)/newlib/Makefile:
	mkdir -p $(@D)
	cd $(@D); $(realpath $(SOURCE_ROOT))/newlib/configure --disable-multilib --disable-libm --without-libm --target=aarch64-none-switch --without-rdimon --prefix=$(LIBTRANSISTOR_HOME)

$(LIBTRANSISTOR_HOME)/lib/libc.a: $(BUILD_DIR)/newlib/Makefile
	$(MAKE) -C $(BUILD_DIR)/newlib/ && $(MAKE) -C $(BUILD_DIR)/newlib/ install

# DIST RULES

DIST_NEWLIB := $(LIBTRANSISTOR_HOME)/lib/libc.a

.PHONY: dist_newlib
dist_newlib: $(DIST_NEWLIB)

# CLEAN RULES

.PHONY: clean_newlib

clean_newlib:
	rm -rf $(BUILD_DIR)/newlib
