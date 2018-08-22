# LIBTRANSISTOR

include mk/transistor_objects.mk
libtransistor_OBJECT_FILES := $(addprefix $(BUILD_DIR)/transistor/,$(libtransistor_OBJECT_NAMES))
libtransistor_CPP_OBJECT_FILES := $(addprefix $(BUILD_DIR)/transistor/cpp/,$(libtransistor_CPP_OBJECT_NAMES))

libtransistor_WARNINGS := -Wall -Wextra -Werror-implicit-function-declaration -Wno-unused-parameter -Wno-unused-command-line-argument -Werror-thread-safety -Werror-return-type -Werror-overloaded-virtual

libtransistor_BUILD_DEPS := $(DIST_TRANSISTOR_HEADERS)
libtransistor_CPP_BUILD_DEPS := $(DIST_TRANSISTOR_CPP_HEADERS)

# ARCHIVE RULES

libtransistor_TARGET_NRO := $(BUILD_DIR)/transistor/libtransistor.nro.a
libtransistor_TARGET_LIB_NRO := $(BUILD_DIR)/transistor/libtransistor.lib.nro.a
libtransistor_TARGET_NSO := $(BUILD_DIR)/transistor/libtransistor.nso.a

$(libtransistor_TARGET_NRO): $(BUILD_DIR)/transistor/crt0.nro.o $(libtransistor_OBJECT_FILES) $(libtransistor_CPP_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

$(libtransistor_TARGET_LIB_NRO): $(BUILD_DIR)/transistor/crt0.lib.nro.o
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

$(libtransistor_TARGET_NSO): $(BUILD_DIR)/transistor/crt0.nso.o $(libtransistor_OBJECT_FILES) $(libtransistor_CPP_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

# BUILD RULES

# Disable stack protector for crt0_common
$(BUILD_DIR)/transistor/crt0_common.o $(BUILD_DIR)/transistor/crt0_common.d: $(SOURCE_ROOT)/lib/crt0_common.c $(libtransistor_BUILD_DEPS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(SOURCE_ROOT)/include/ -I$(SOURCE_ROOT)/pthread/ -I$(SOURCE_ROOT)/pthread/sys/switch/ $(libtransistor_WARNINGS) -MMD -MP -fno-stack-protector -c -o $(BUILD_DIR)/transistor/crt0_common.o $<

# Disable stack protector for ld
$(BUILD_DIR)/transistor/ld/%.o $(BUILD_DIR)/transistor/ld/%.d: $(SOURCE_ROOT)/lib/ld/%.c $(libtransistor_BUILD_DEPS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(SOURCE_ROOT)/include/ $(libtransistor_WARNINGS) -MMD -MP -fno-stack-protector -c -o $(BUILD_DIR)/transistor/ld/$*.o $<

# Rule for building library C files
$(BUILD_DIR)/transistor/%.o $(BUILD_DIR)/transistor/%.d: $(SOURCE_ROOT)/lib/%.c $(libtransistor_BUILD_DEPS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(SOURCE_ROOT)/include/ $(libtransistor_WARNINGS) -MMD -MP -c -o $(BUILD_DIR)/transistor/$*.o $<

# Rule for building library C++ files
$(BUILD_DIR)/transistor/%.o $(BUILD_DIR)/transistor/%.d: $(SOURCE_ROOT)/lib/%.cpp $(libtransistor_CPP_BUILD_DEPS)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -I$(SOURCE_ROOT)/include/ $(libtransistor_WARNINGS) -MMD -MP -c -o $(BUILD_DIR)/transistor/$*.o $<

#include $(libtransistor_OBJECT_FILES:.o=.d)

# Rule for building library assembly files
$(BUILD_DIR)/transistor/%.o $(BUILD_DIR)/transistor/%.d: $(SOURCE_ROOT)/lib/%.S $(libtransistor_BUILD_DEPS)
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $(BUILD_DIR)/transistor/$*.o
	touch $(BUILD_DIR)/transistor/$*.d

# DIST RULES

DIST_TRANSISTOR := \
	$(DIST_TRANSISTOR_HEADERS) \
	$(DIST_TRANSISTOR_CPP_HEADERS) \
	$(LIBTRANSISTOR_HOME)/lib/libtransistor.nro.a \
	$(LIBTRANSISTOR_HOME)/lib/libtransistor.lib.nro.a \
	$(LIBTRANSISTOR_HOME)/lib/libtransistor.nso.a \

$(LIBTRANSISTOR_HOME)/lib/libtransistor.nro.a: $(libtransistor_TARGET_NRO)
	install -d $(@D)
	install $< $@

$(LIBTRANSISTOR_HOME)/lib/libtransistor.lib.nro.a: $(libtransistor_TARGET_LIB_NRO)
	install -d $(@D)
	install $< $@

$(LIBTRANSISTOR_HOME)/lib/libtransistor.nso.a: $(libtransistor_TARGET_NSO)
	install -d $(@D)
	install $< $@

.PHONY: dist_transistor
dist_transistor: $(DIST_TRANSISTOR)

# CLEAN RULES

.PHONY: clean_transistor clean

clean_transistor:
	rm -rf $(BUILD_DIR)/transistor/
	rm -rf $(LIBTRANSISTOR_HOME)/lib/libtransistor.nro.a
	rm -rf $(LIBTRANSISTOR_HOME)/lib/libtransistor.nro.lib.a
	rm -rf $(LIBTRANSISTOR_HOME)/lib/libtransistor.nso.a

# add to default target
default: $(LIBTRANSISTOR_HOME)/lib/libtransistor.nro.a \
	$(LIBTRANSISTOR_HOME)/lib/libtransistor.lib.nro.a \
	$(LIBTRANSISTOR_HOME)/lib/libtransistor.nso.a \
