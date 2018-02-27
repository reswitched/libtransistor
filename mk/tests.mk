# LIBTRANSISTOR TESTS

libtransistor_TESTS := malloc bsd_ai_packing bsd sfdnsres nv helloworld hid hexdump args ssp stdin multiple_set_heap_size vi gpu display am sdl sqfs_img audio_output init_fini_arrays fs_releases_inodes ipc_server pthread cpp alloc_pages unwind cpp_exceptions cpp_dynamic_memory

# RUN RULES

run_tests: run_helloworld_test run_hexdump_test run_malloc_test run_bsd_ai_packing_test run_bsd_test run_sfdnsres_test run_multiple_set_heap_size_test run_init_fini_arrays_test run_fs_releases_inodes_test run_cpp_test run_alloc_pages_test run_unwind_test run_cpp_exceptions_test run_cpp_dynamic_memory_test

run_bsd_test: $(LIBTRANSISTOR_HOME)/build/test/test_bsd.nro $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb
	$(RUBY) $(LIBTRANSISTOR_HOME)/test_helpers/bsd.rb $(MEPHISTO)

run_sfdnsres_test: $(LIBTRANSISTOR_HOME)/build/test/test_sfdnsres.nro
	$(MEPHISTO) --enable-sockets --load-nro $<

run_ssp_test: $(LIBTRANSISTOR_HOME)/build/test/test_ssp.nro
	$(MEPHISTO) --enable-sockets --load-nro $<

run_%_test: $(LIBTRANSISTOR_HOME)/build/test/test_%.nro
	$(MEPHISTO) --load-nro $<

# LINK RULES

$(LIBTRANSISTOR_HOME)/build/test/%.nro.so: $(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_HOME)/build/test/%.squashfs.o $(LIBTRANSISTOR_NRO_DEPS)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(LIBTRANSISTOR_HOME)/build/test/$*.squashfs.o $(LIBTRANSISTOR_NRO_LDFLAGS)

$(LIBTRANSISTOR_HOME)/build/test/%.nso.so: $(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_HOME)/build/test/%.squashfs.o $(LIBTRANSISTOR_NSO_DEPS)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(LIBTRANSISTOR_HOME)/build/test/$*.squashfs.o $(LIBTRANSISTOR_NSO_LDFLAGS)

# BUILD RULES

$(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_HOME)/build/test/%.d: $(LIBTRANSISTOR_HOME)/test/%.c $(LIBTRANSISTOR_COMMON_LIB_DEPS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(libtransistor_WARNINGS) -MMD -MP -c -o $(LIBTRANSISTOR_HOME)/build/test/$*.o $<

$(LIBTRANSISTOR_HOME)/build/test/%.o $(LIBTRANSISTOR_HOME)/build/test/%.d: $(LIBTRANSISTOR_HOME)/test/%.cpp $(CXX_LIB_DEPS)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(libtransistor_WARNINGS) -MMD -MP -c -o $(LIBTRANSISTOR_HOME)/build/test/$*.o $<

include $(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .d,$(libtransistor_TESTS)))

# SQUASHFS RULES

$(LIBTRANSISTOR_HOME)/build/test/%.squashfs.o: $(LIBTRANSISTOR_HOME)/build/test/%.squashfs
	mkdir -p $(@D)
	$(LD) -s -r -b binary -m aarch64elf -T $(LIBTRANSISTOR_HOME)/fs.T -o $@ $<

$(LIBTRANSISTOR_HOME)/build/empty_file:
	touch $@

$(LIBTRANSISTOR_HOME)/build/test/%.squashfs: $(LIBTRANSISTOR_HOME)/test/fs_%/*
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp xz -nopad -noappend

$(LIBTRANSISTOR_HOME)/build/test/%.squashfs: $(LIBTRANSISTOR_HOME)/build/empty_file
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp xz -nopad -noappend

# CLEAN RULES

clean_test:
	rm -rf $(LIBTRANSISTOR_HOME)/build/test

# add tests to default target

default: \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nro,$(libtransistor_TESTS))) \
	$(addprefix $(LIBTRANSISTOR_HOME)/build/test/test_,$(addsuffix .nso,$(libtransistor_TESTS)))
