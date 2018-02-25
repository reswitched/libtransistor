# PTHREAD

pthread_SRCS=	rthread_attr.c rthread_barrier.c rthread_barrier_attr.c rthread_cond.c rthread_condattr.c rthread_debug.c rthread_getcpuclockid.c rthread_internal.c rthread_mutex.c rthread_mutex_prio.c rthread_mutexattr.c rthread_once.c rthread_rwlock.c rthread_rwlockattr.c rthread_sched.c rthread_sem.c rthread_sig.c rthread_spin_lock.c rthread_thread.c rthread_tls.c sched_prio.c sys/switch/phal.c
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

# ARCHIVE RULES

$(pthread_TARGET): $(pthread_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

# BUILD RULES

$(BUILD_DIR)/pthread/%.o: $(SOURCE_ROOT)/pthread/%.c dist_transistor_headers
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(WARNINGS) $(pthread_CC_FLAGS) -c -o $@ $<

# DIST RULES

dist_pthread: $(pthread_TARGET) $(SOURCE_ROOT)/pthread/*.h
	mkdir -p $(LIBTRANSISTOR_HOME)/include/
	cp -rt $(LIBTRANSISTOR_HOME)/include/ $(SOURCE_ROOT)/pthread/*.h
	install -Dt $(LIBTRANSISTOR_HOME)/lib/ $(pthread_TARGET)

# CLEAN RULES

.PHONY: clean_pthread

clean_pthread:
	rm -fr build/pthread
