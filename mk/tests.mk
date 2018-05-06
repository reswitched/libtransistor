# LIBTRANSISTOR TESTS

libtransistor_TESTS := malloc bsd_ai_packing bsd sfdnsres nv helloworld hid hexdump args ssp stdin multiple_set_heap_size vi gpu display am sqfs_img audio_output init_fini_arrays ipc_server pthread ipc_fs fs_stress cpp unwind cpp_exceptions cpp_dynamic_memory hid_init_stress usb usb_serial thread mutex override_heap # fs_release_inodes

# RUN RULES

run_tests: run_helloworld_test run_hexdump_test run_malloc_test run_bsd_ai_packing_test run_bsd_test run_sfdnsres_test run_multiple_set_heap_size_test run_init_fini_arrays_test run_ipc_fs_test run_fs_stress_test run_cpp_test run_unwind_test run_cpp_exceptions_test run_cpp_dynamic_memory_test run_thread_test run_mutex_test run_override_heap_test # run_fs_releases_inodes_test

run_bsd_test: $(BUILD_DIR)/test/test_bsd.nro $(SOURCE_ROOT)/test_helpers/bsd.rb
	$(RUBY) $(SOURCE_ROOT)/test_helpers/bsd.rb $(MEPHISTO)

run_sfdnsres_test: $(BUILD_DIR)/test/test_sfdnsres.nro
	$(MEPHISTO) --enable-sockets --initialize-memory --load-nro $<

run_ssp_test: $(BUILD_DIR)/test/test_ssp.nro
	$(MEPHISTO) --enable-sockets --initialize-memory --load-nro $<

run_fs_stress_test: $(BUILD_DIR)/test/test_fs_stress.nro
	mkdir -p $(BUILD_DIR)/SwitchFS/SDCard/
	echo "test text" > $(BUILD_DIR)/SwitchFS/SDCard/test_file
	cd $(BUILD_DIR); $(realpath $(MEPHISTO)) --initialize-memory --load-nro $(realpath $<)

run_ipc_fs_test: $(BUILD_DIR)/test/test_fs_stress.nro
	mkdir -p $(BUILD_DIR)/SwitchFS/SDCard/
	echo "test text" > $(BUILD_DIR)/SwitchFS/SDCard/test_file
	cd $(BUILD_DIR); $(realpath $(MEPHISTO)) --initialize-memory --load-nro $(realpath $<)

run_%_test: $(BUILD_DIR)/test/test_%.nro
	$(MEPHISTO) --initialize-memory --load-nro $<

# LINK RULES

$(BUILD_DIR)/test/%.nro.so: $(BUILD_DIR)/test/%.o $(BUILD_DIR)/test/%.squashfs.o $(DIST)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(BUILD_DIR)/test/$*.squashfs.o $(LIBTRANSISTOR_NRO_LDFLAGS)

$(BUILD_DIR)/test/%.nso.so: $(BUILD_DIR)/test/%.o $(BUILD_DIR)/test/%.squashfs.o $(DIST)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(BUILD_DIR)/test/$*.squashfs.o $(LIBTRANSISTOR_NSO_LDFLAGS)

# BUILD RULES

$(BUILD_DIR)/test/%.o $(BUILD_DIR)/test/%.d: $(SOURCE_ROOT)/test/%.c $(DIST)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(libtransistor_WARNINGS) -MMD -MP -c -o $(BUILD_DIR)/test/$*.o $<

$(BUILD_DIR)/test/%.o $(BUILD_DIR)/test/%.d: $(SOURCE_ROOT)/test/%.cpp $(DIST)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(libtransistor_WARNINGS) -MMD -MP -c -o $(BUILD_DIR)/test/$*.o $<

#include $(addprefix $(BUILD_DIR)/test/test_,$(addsuffix .d,$(libtransistor_TESTS)))

# SQUASHFS RULES

$(BUILD_DIR)/test/%.squashfs.o: $(BUILD_DIR)/test/%.squashfs $(LIBTRANSISTOR_HOME)/fs.T
	mkdir -p $(@D)
	$(LD) -s -r -b binary -m aarch64elf -T $(LIBTRANSISTOR_HOME)/fs.T -o $@ $<

$(BUILD_DIR)/empty_file:
	touch $@

$(BUILD_DIR)/test/%.squashfs: $(LIBTRANSISTOR_HOME)/test/fs_%/*
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp xz -nopad -noappend

$(BUILD_DIR)/test/%.squashfs: $(BUILD_DIR)/empty_file
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp xz -nopad -noappend

# CLEAN RULES

clean_test:
	rm -rf $(BUILD_DIR)/test

# add tests to default target

default: \
	$(addprefix $(BUILD_DIR)/test/test_,$(addsuffix .nro,$(libtransistor_TESTS))) \
	$(addprefix $(BUILD_DIR)/test/test_,$(addsuffix .nso,$(libtransistor_TESTS)))
