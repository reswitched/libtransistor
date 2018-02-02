# OPENLIBM

# ARCHIVE RULES

$(LIBTRANSISTOR_HOME)/build/openlibm/libm.a: $(openlibm_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

# BUILD RULES

$(LIBTRANSISTOR_HOME)/build/openlibm/%.o: $(LIBTRANSISTOR_HOME)/openlibm/src/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -o $@ $<
