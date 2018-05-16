# LIBTRANSISTOR TESTS

libtransistor_TESTS := malloc bsd_ai_packing bsd sfdnsres nv helloworld hid hexdump args ssp stdin vi gpu display am sqfs_img audio_output init_fini_arrays ipc_server pthread ipc_fs fs_stress cpp unwind cpp_exceptions cpp_dynamic_memory hid_init_stress usb usb_serial thread mutex override_heap # fs_release_inodes
libtransistor_DYNAMIC_TESTS := simple dlfcn bad_resolution

# RUN RULES

run_tests: run_helloworld_test run_hexdump_test run_malloc_test run_bsd_ai_packing_test run_bsd_test run_sfdnsres_test run_init_fini_arrays_test run_ipc_fs_test run_fs_stress_test run_cpp_test run_unwind_test run_cpp_exceptions_test run_cpp_dynamic_memory_test run_thread_test run_mutex_test run_override_heap_test run_dynamic_simple_test run_dynamic_bad_resolution_test # run_fs_releases_inodes_test

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

run_dynamic_%_test: $(BUILD_DIR)/test/dynamic/test_%.nro
	$(MEPHISTO) --initialize-memory --load-nro $<

run_dynamic_bad_resolution_test: $(BUILD_DIR)/test/dynamic/test_bad_resolution.nro
	$(MEPHISTO) --initialize-memory --load-nro $<; test $$? -eq 221

# LINK RULES

$(BUILD_DIR)/test/dynamic/test_simple.nro.so: \
	$(BUILD_DIR)/test/dynamic/test_simple.o \
	$(BUILD_DIR)/test/dynamic/test_simple.squashfs.o \
	$(BUILD_DIR)/test/dynamic/libdynamic_simple.nro.so \
	$(BUILD_DIR)/test/dynamic/libdynamic_simple.nro \
	$(DIST)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(BUILD_DIR)/test/dynamic/test_simple.squashfs.o $(LIBTRANSISTOR_NRO_LDFLAGS) -L $(realpath $(BUILD_DIR)/test/dynamic)/ -ldynamic_simple.nro

# link this test against libdynamic_simple, but give it libdynamic_bad_resolution
# at runtime
$(BUILD_DIR)/test/dynamic/test_bad_resolution.nro.so: \
	$(BUILD_DIR)/test/dynamic/test_bad_resolution.o \
	$(BUILD_DIR)/test/dynamic/test_bad_resolution.squashfs.o \
	$(BUILD_DIR)/test/dynamic/libdynamic_bad_resolution.nro.so \
	$(BUILD_DIR)/test/dynamic/bad_resolution/libdynamic_simple.nro \
	$(DIST)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(BUILD_DIR)/test/dynamic/test_bad_resolution.squashfs.o $(LIBTRANSISTOR_NRO_LDFLAGS) -L $(realpath $(BUILD_DIR)/test/dynamic)/ -ldynamic_simple.nro

$(BUILD_DIR)/test/dynamic/test_dlfcn.nro.so: \
	$(BUILD_DIR)/test/dynamic/test_dlfcn.o \
	$(BUILD_DIR)/test/dynamic/test_dlfcn.squashfs.o \
	$(BUILD_DIR)/test/dynamic/libdynamic_dlfcn.nro.so \
	$(BUILD_DIR)/test/dynamic/libdynamic_dlfcn.nro \
	$(DIST)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(BUILD_DIR)/test/dynamic/test_dlfcn.squashfs.o $(LIBTRANSISTOR_NRO_LDFLAGS) -L $(realpath $(BUILD_DIR)/test/dynamic)/

$(BUILD_DIR)/test/test_%.nro.so: $(BUILD_DIR)/test/test_%.o $(BUILD_DIR)/test/test_%.squashfs.o $(DIST)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(BUILD_DIR)/test/test_$*.squashfs.o $(LIBTRANSISTOR_NRO_LDFLAGS)

$(BUILD_DIR)/test/test_%.nso.so: $(BUILD_DIR)/test/test_%.o $(BUILD_DIR)/test/test_%.squashfs.o $(DIST)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -o $@ $< $(BUILD_DIR)/test/test_$*.squashfs.o $(LIBTRANSISTOR_NSO_LDFLAGS)

$(BUILD_DIR)/test/dynamic/libdynamic_%.nro.so: $(BUILD_DIR)/test/dynamic/libdynamic_%.o $(DIST)
	mkdir -p $(@D)
	$(LD) $(LD_SHARED_LIBRARY_FLAGS) -o $@ $< -ltransistor.lib.nro $(LIBTRANSISTOR_COMMON_LDFLAGS)

$(BUILD_DIR)/test/dynamic/libdynamic_%.nro: $(BUILD_DIR)/test/dynamic/libdynamic_%.nro.so
	$(PYTHON3) $(LIBTRANSISTOR_HOME)/tools/elf2nxo.py $< $@ nro

# compile libdynamic_bad_resolution, but name it libdynamic_simple
$(BUILD_DIR)/test/dynamic/bad_resolution/libdynamic_simple.nro: $(BUILD_DIR)/test/dynamic/libdynamic_bad_resolution.nro.so
	mkdir -p $(@D)
	$(PYTHON3) $(LIBTRANSISTOR_HOME)/tools/elf2nxo.py $< $@ nro

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


$(BUILD_DIR)/test/dynamic/test_bad_resolution.squashfs: $(BUILD_DIR)/test/dynamic/bad_resolution/libdynamic_simple.nro
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp xz -nopad -noappend

$(BUILD_DIR)/test/dynamic/test_%.squashfs:  $(BUILD_DIR)/test/dynamic/libdynamic_%.nro
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp xz -nopad -noappend

$(BUILD_DIR)/test/test_%.squashfs: $(LIBTRANSISTOR_HOME)/test/fs_test_%/*
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp xz -nopad -noappend

$(BUILD_DIR)/test/test_%.squashfs: $(BUILD_DIR)/empty_file
	mkdir -p $(@D)
	mksquashfs $^ $@ -comp xz -nopad -noappend

# CLEAN RULES

clean_test:
	rm -rf $(BUILD_DIR)/test

# add tests to default target

default: \
	$(addprefix $(BUILD_DIR)/test/test_,$(addsuffix .nro,$(libtransistor_TESTS))) \
	$(addprefix $(BUILD_DIR)/test/test_,$(addsuffix .nso,$(libtransistor_TESTS))) \
	$(addprefix $(BUILD_DIR)/test/dynamic/test_,$(addsuffix .nro,$(libtransistor_DYNAMIC_TESTS))) \
