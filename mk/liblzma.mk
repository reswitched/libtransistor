# LIBLZMA

$(LIBTRANSISTOR_HOME)/build/xz/Makefile: $(LIBTRANSISTOR_HOME)/xz/configure
	mkdir -p $(@D)
	cd $(@D); $(LIBTRANSISTOR_HOME)/xz/configure \
		"CFLAGS=$(CFLAGS)" \
		"CC=$(CC)" "AR=$(AR)" \
		"RANLIB=$(RANLIB)" \
		"LDFLAGS=-L$(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/ -lc -lm" \
		--host=aarch64-none-none \
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

$(LIB_DEP_LIBLZMA): $(LIBTRANSISTOR_HOME)/build/xz/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/xz/
