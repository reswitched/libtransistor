# LIBCXX / LIBCXXABI / LIBUNWIND

$(LIB_DEP_LIBCXX): $(LIBTRANSISTOR_HOME)/build/libcxx/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/libcxx

$(LIB_DEP_LIBCXXABI): $(LIBTRANSISTOR_HOME)/build/libcxxabi/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/libcxxabi

$(LIB_DEP_LIBUNWIND): $(LIBTRANSISTOR_HOME)/build/libunwind/Makefile
	$(MAKE) -C $(LIBTRANSISTOR_HOME)/build/libunwind

$(LIBTRANSISTOR_HOME)/build/libcxx/Makefile: $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a $(COMPILER_RT_BUILTINS_LIB) $(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a $(LIBTRANSISTOR_HOME)/build/openlibm/libm.a
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(LIBTRANSISTOR_HOME)/libcxx \
		-DLIBCXX_ENABLE_SHARED=NO \
		-DLIBCXX_USE_COMPILER_RT=ON \
		-DLIBCXX_CXX_ABI=libcxxabi \
		-DLIBCXX_CXX_ABI_INCLUDE_PATHS=$(LIBTRANSISTOR_HOME)/libcxxabi/include \
		-DLIBCXX_ENABLE_EXPERIMENTAL_LIBRARY=NO \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_CXX_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_CXX_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_AR="$(AR)" \
		-DCMAKE_EXE_LINKER_FLAGS="-Wl,-T$(LIBTRANSISTOR_HOME)/link.T -fuse-ld=lld $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a $(COMPILER_RT_BUILTINS_LIB) $(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a $(LIBTRANSISTOR_HOME)/build/openlibm/libm.a" \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux

$(LIBTRANSISTOR_HOME)/build/libcxxabi/Makefile: $(LIBCXX_LIB)
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(LIBTRANSISTOR_HOME)/libcxxabi \
		-DLIBCXXABI_USE_LLVM_UNWINDER=ON \
		-DLIBCXXABI_ENABLE_STATIC_UNWINDER=ON \
		-DLIBCXXABI_LIBCXX_LIBRARY_PATH="$(LIBTRANSISTOR_HOME)/build/libcxx/lib" \
		-DLIBCXXABI_LIBCXX_INCLUDES="$(LIBTRANSISTOR_HOME)/libcxx/include" \
		-DLIBCXXABI_ENABLE_SHARED=OFF \
		-DLIBCXXABI_BAREMETAL=ON \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS="$(CC_FLAGS)" \
		-DCMAKE_C_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_CXX_FLAGS="$(CXX_FLAGS)" \
		-DCMAKE_CXX_COMPILER_TARGET="aarch64-none-linux-gnu" \
		-DCMAKE_AR="$(AR)" \
		-DCMAKE_EXE_LINKER_FLAGS="-Wl,-T$(LIBTRANSISTOR_HOME)/link.T -fuse-ld=lld $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a $(COMPILER_RT_BUILTINS_LIB) $(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a" \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux

$(LIBTRANSISTOR_HOME)/build/libunwind/Makefile: $(LIBCXX_LIB)
	mkdir -p $(@D)
	cd $(@D); cmake -G "Unix Makefiles" $(LIBTRANSISTOR_HOME)/libunwind \
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
		-DCMAKE_EXE_LINKER_FLAGS="-Wl,-T$(LIBTRANSISTOR_HOME)/link.T -fuse-ld=lld $(LIBTRANSISTOR_HOME)/build/newlib/aarch64-none-switch/newlib/libc.a $(COMPILER_RT_BUILTINS_LIB) $(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a" \
		-DLLVM_CONFIG_PATH=llvm-config$(LLVM_POSTFIX) \
		-DCMAKE_SYSTEM_NAME=Linux
