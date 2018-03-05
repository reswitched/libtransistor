# SDL2

$(LIB_DEP_SDL2): $(BUILD_DIR)/sdl2/Makefile $(DIST_TRANSISTOR_HEADERS)
	$(MAKE) -C $(BUILD_DIR)/sdl2/
	$(MAKE) -C $(BUILD_DIR)/sdl2/ install

# "LDFLAGS=-L$(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/ -lc -lm" \

$(BUILD_DIR)/sdl2/Makefile: $(DIST_NEWLIB) $(DIST_TRANSISTOR_SUPPORT)
	mkdir -p $(@D)
	cd $(@D); $(realpath $(SOURCE_ROOT))/sdl2/configure \
		"CFLAGS=$(CFLAGS)" \
		"CC=$(CC)" "AR=$(AR)" \
		"RANLIB=$(RANLIB)" \
		--host=aarch64-none-switch \
		--disable-audio \
		--disable-joystick \
		--disable-power \
		--disable-filesystem \
		--disable-threads \
		--disable-cpuinfo \
		--enable-timers \
		--enable-video \
		--disable-shared \
		--enable-static \
		--prefix=$(LIBTRANSISTOR_HOME)

# DIST RULES

DIST_SDL2 := $(LIB_DEP_SDL2)

.PHONY: dist_sdl2
dist_sdl2: $(LIB_DEP_SDL2)

# CLEAN RULES

.PHONY: clean_sdl2

clean_sdl2:
	rm -rf $(BUILD_DIR)/sdl2 $(BUILD_DIR)/sdl2_install
