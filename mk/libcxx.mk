# LIBCXX / LIBCXXABI / LIBUNWIND

$(LIB_DEP_LIBCXX): $(BUILD_DIR)/libcxx/Makefile
	$(MAKE) -C $(BUILD_DIR)/libcxx all install
	touch $@

$(LIB_DEP_LIBCXXABI): $(BUILD_DIR)/libcxxabi/Makefile
	$(MAKE) -C $(BUILD_DIR)/libcxxabi all install
	touch $@

$(LIB_DEP_LIBUNWIND): $(BUILD_DIR)/libunwind/Makefile
	$(MAKE) -C $(BUILD_DIR)/libunwind all install
	touch $@

# DIST RULES

DIST_LIBCXX := $(LIB_DEP_LIBCXX)
DIST_LIBCXXABI := $(LIB_DEP_LIBCXXABI)

# libunwind doesn't install these headers because they conflict
# with things on some systems, but they don't conflict with anything
# here and we need them
DIST_LIBUNWIND := $(LIB_DEP_LIBUNWIND) \
	$(LIBTRANSISTOR_HOME)/include/libunwind.h \
	$(LIBTRANSISTOR_HOME)/include/__libunwind_config.h

$(LIBTRANSISTOR_HOME)/include/%: $(SOURCE_ROOT)/libunwind/include/%
	install -d $(@D)
	install $< $@

.PHONY: dist_libcxx dist_libcxxabi dist_libunwind
dist_libcxx: $(DIST_LIBCXX)
dist_libcxxabi: $(DIST_LIBCXXABI)
dist_libunwind: $(DIST_LIBUNWIND)

# CMAKE RULES

LIBCXX_CMAKE_EXE_LINKER_FLAGS := "-Wl,-T$(LIBTRANSISTOR_HOME)/link.T -fuse-ld=lld -L$(LIBTRANSISTOR_HOME)/lib -lc -lclang_rt.builtins-aarch64 -lpthread -lm"

$(BUILD_DIR)/libcxx/Makefile: $(DIST_NEWLIB) $(DIST_COMPILER_RT) $(DIST_PTHREAD_HEADERS) $(DIST_OPENLIBM) $(DIST_TRANSISTOR_SUPPORT)
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(realpath $(SOURCE_ROOT))/libcxx \
		-DLIBCXX_ENABLE_SHARED=NO \
		-DLIBCXX_USE_COMPILER_RT=ON \
		-DLIBCXX_CXX_ABI=libcxxabi \
		-DLIBCXX_CXX_ABI_INCLUDE_PATHS=$(realpath $(SOURCE_ROOT))/libcxxabi/include \
		-DLIBCXX_ENABLE_EXPERIMENTAL_LIBRARY=NO \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_CXX_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_CXX_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_AR="$(AR)" \
		-DCMAKE_EXE_LINKER_FLAGS=$(LIBCXX_CMAKE_EXE_LINKER_FLAGS) \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux \
		-DCMAKE_INSTALL_PREFIX=$(LIBTRANSISTOR_HOME)

$(BUILD_DIR)/libcxxabi/Makefile: $(DIST_LIBCXX) $(DIST_TRANSISTOR_SUPPORT)
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(realpath $(SOURCE_ROOT))/libcxxabi \
		-DLIBCXXABI_USE_LLVM_UNWINDER=ON \
		-DLIBCXXABI_ENABLE_STATIC_UNWINDER=ON \
		-DLIBCXXABI_LIBCXX_LIBRARY_PATH="$(LIBTRANSISTOR_HOME)/lib" \
		-DLIBCXXABI_LIBCXX_INCLUDES="$(LIBTRANSISTOR_HOME)/include" \
		-DLIBCXXABI_ENABLE_SHARED=OFF \
		-DLIBCXXABI_BAREMETAL=ON \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_CXX_FLAGS="$(CXX_FLAGS)" \
		-DCMAKE_CXX_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_AR="$(AR)" \
		-DCMAKE_EXE_LINKER_FLAGS=$(LIBCXX_CMAKE_EXE_LINKER_FLAGS) \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux \
		-DCMAKE_INSTALL_PREFIX=$(LIBTRANSISTOR_HOME)

$(BUILD_DIR)/libunwind/Makefile: $(DIST_LIBCXX) $(DIST_TRANSISTOR_SUPPORT)
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(realpath $(SOURCE_ROOT))/libunwind \
		-DLIBUNWIND_ENABLE_SHARED=OFF \
		-DLIBUNWIND_ENABLE_ARM_WMMX=ON \
		-DLIBUNWIND_USE_COMPILER_RT=ON \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS="$(CC_FLAGS) -D_LIBUNWIND_IS_BAREMETAL=1" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_CXX_FLAGS="$(CXX_FLAGS) -D_LIBUNWIND_IS_BAREMETAL=1" \
		-DCMAKE_CXX_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_AR="$(AR)" \
		-DCMAKE_EXE_LINKER_FLAGS=$(LIBCXX_CMAKE_EXE_LINKER_FLAGS) \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux \
		-DCMAKE_INSTALL_PREFIX=$(LIBTRANSISTOR_HOME)
