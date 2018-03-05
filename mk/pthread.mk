# PTHREAD

pthread_SRCS = rthread_attr.c rthread_barrier.c rthread_barrier_attr.c rthread_cond.c rthread_condattr.c rthread_debug.c rthread_getcpuclockid.c rthread_internal.c rthread_mutex.c rthread_mutex_prio.c rthread_mutexattr.c rthread_once.c rthread_rwlock.c rthread_rwlockattr.c rthread_sched.c rthread_sem.c rthread_sig.c rthread_spin_lock.c rthread_thread.c rthread_tls.c sched_prio.c sys/switch/phal.c
pthread_HEADERS = pthread.h sys/_pthreadtypes.h
pthread_OBJECT_FILES := $(addprefix $(BUILD_DIR)/pthread/,$(pthread_SRCS:.c=.o))

pthread_CC_FLAGS := \
	-I$(SOURCE_ROOT)/pthread \
	-I$(SOURCE_ROOT)/pthread/include \
	-I$(SOURCE_ROOT)/pthread/sys/switch \
	-Wno-incompatible-pointer-types-discards-qualifiers \
	-Wno-unused-variable \
	-Wno-unused-function \
	-Wno-unused-label

pthread_TARGET := $(BUILD_DIR)/pthread/libpthread.a

pthread_BUILD_DEPS := $(DIST_TRANSISTOR_SUPPORT) $(DIST_NEWLIB)

# ARCHIVE RULES

$(pthread_TARGET): $(pthread_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

# DIST RULES

DIST_PTHREAD_HEADERS := $(addprefix $(LIBTRANSISTOR_HOME)/include/,$(pthread_HEADERS))
DIST_PTHREAD := $(LIBTRANSISTOR_HOME)/lib/libpthread.a

$(LIBTRANSISTOR_HOME)/lib/libpthread.a: $(pthread_TARGET)
	install -d $(@D)
	install $< $@

$(LIBTRANSISTOR_HOME)/include/%: $(SOURCE_ROOT)/pthread/include/%
	install -d $(@D)
	install $< $@

.PHONY: dist_pthread_headers dist_pthread
dist_pthread_headers: $(DIST_PTHREAD_HEADERS)
dist_pthread: $(DIST_PTHREAD)

# BUILD RULES

$(BUILD_DIR)/pthread/sys/switch/phal.o: $(SOURCE_ROOT)/pthread/sys/switch/phal.c $(pthread_BUILD_DEPS) $(DIST_TRANSISTOR_HEADERS) $(DIST_PTHREAD_HEADERS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(WARNINGS) $(pthread_CC_FLAGS) -c -o $@ $<

$(BUILD_DIR)/pthread/%.o: $(SOURCE_ROOT)/pthread/%.c $(pthread_BUILD_DEPS) $(DIST_PTHREAD_HEADERS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(WARNINGS) $(pthread_CC_FLAGS) -c -o $@ $<

# CLEAN RULES

.PHONY: clean_pthread

clean_pthread:
	rm -rf $(BUILD_DIR)/pthread
