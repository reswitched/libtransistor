# NEWLIB

$(LIBTRANSISTOR_HOME)/build/newlib/Makefile:
	mkdir -p $(@D)
	cd $(@D); $(LIBTRANSISTOR_HOME)/newlib/configure --disable-multilib --target=aarch64-none-switch --without-rdimon

$(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libm.a $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a: $(LIBTRANSISTOR_HOME)/build/newlib/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/newlib/

# CLEAN RULES

.PHONY: clean_newlib

clean_newlib:
	rm -rf build/newlib
