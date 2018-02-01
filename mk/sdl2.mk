# SDL2

$(LIBTRANSISTOR_HOME)/build/sdl2_install/lib/libSDL2.a: $(LIBTRANSISTOR_HOME)/build/sdl2/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/sdl2/
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/sdl2/ install

$(LIBTRANSISTOR_HOME)/build/sdl2/Makefile: $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libm.a $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a
	mkdir -p $(@D)
	cd $(@D); $(LIBTRANSISTOR_HOME)/sdl2/configure \
		"CFLAGS=$(CFLAGS)" \
		"CC=$(CC)" "AR=$(AR)" \
		"RANLIB=$(RANLIB)" \
		"LDFLAGS=-L$(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/ -lc -lm" \
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
		--prefix=$(LIBTRANSISTOR_HOME)/build/sdl2_install/

# CLEAN RULES

.PHONY: clean_sdl2

clean_sdl2:
	rm -rf build/sdl2 build/sdl2_install
