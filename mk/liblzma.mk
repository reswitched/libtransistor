# LIBLZMA

$(BUILD_DIR)/xz/Makefile: $(SOURCE_ROOT)/xz/configure
	mkdir -p $(@D)
	cd $(SOURCE_ROOT)/xz && touch configure.ac aclocal.m4 Makefile.am configure Makefile.in # these are up to date
	cd $(@D) && $(realpath $(SOURCE_ROOT))/xz/configure \
		"CFLAGS=$(CFLAGS)" \
		"CC=$(CC)" "AR=$(AR)" \
		"RANLIB=$(RANLIB)" \
		--host=aarch64-none-none \
		--prefix=$(LIBTRANSISTOR_HOME) \
		--disable-xz \
		--disable-xzdec \
		--disable-lzmadec \
		--disable-lzmainfo \
		--disable-lzma-links \
		--disable-scripts \
		--disable-doc \
		--disable-threads \
		--disable-encoders\
		--disable-shared

$(LIB_DEP_LIBLZMA): $(BUILD_DIR)/xz/Makefile
	$(MAKE) -C $(BUILD_DIR)/xz/ && $(MAKE) -C $(BUILD_DIR)/xz/ install

DIST_LIBLZMA := $(LIB_DEP_LIBLZMA)

dist_liblzma: $(DIST_LIBLZMA)

.PHONY: dist_liblzma

# CLEAN RULES

.PHONY: clean_liblzma

clean_liblzma:
	rm -rf $(BUILD_DIR)/xz
