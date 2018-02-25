# NEWLIB

$(BUILD_DIR)/newlib/Makefile:
	mkdir -p $(@D)
	cd $(@D); $(realpath $(SOURCE_ROOT))/newlib/configure --disable-multilib --target=aarch64-none-switch --without-rdimon --prefix=$(LIBTRANSISTOR_HOME)

$(LIBTRANSISTOR_HOME)/lib/libc.a: $(BUILD_DIR)/newlib/Makefile
	$(MAKE) -C $(BUILD_DIR)/newlib/ && $(MAKE) -C $(BUILD_DIR)/newlib/ install

# DIST RULES

dist_newlib: $(LIBTRANSISTOR_HOME)/lib/libc.a

.PHONY: dist_newlib

# CLEAN RULES

.PHONY: clean_newlib

clean_newlib:
	rm -rf build/newlib
