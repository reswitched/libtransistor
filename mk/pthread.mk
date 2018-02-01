# PTHREAD

pthread_SRCS=	rthread_attr.c rthread_barrier.c rthread_barrier_attr.c rthread_cond.c rthread_condattr.c rthread_debug.c rthread_getcpuclockid.c rthread_internal.c rthread_mutex.c rthread_mutex_prio.c rthread_mutexattr.c rthread_once.c rthread_rwlock.c rthread_rwlockattr.c rthread_sched.c rthread_sem.c rthread_sig.c rthread_spin_lock.c rthread_thread.c rthread_tls.c sched_prio.c sys/switch/phal.c
pthread_OBJECT_FILES := $(addprefix $(LIBTRANSISTOR_HOME)/build/pthread/,$(pthread_SRCS:.c=.o))

pthread_CC_FLAGS := \
	-I$(LIBTRANSISTOR_HOME)/pthread \
	-I$(LIBTRANSISTOR_HOME)/pthread/sys/switch \
	-Wno-incompatible-pointer-types-discards-qualifiers \
	-Wno-unused-variable \
	-Wno-unused-function \
	-Wno-unused-label

# ARCHIVE RULES

$(LIBTRANSISTOR_HOME)/build/pthread/libpthread.a: $(pthread_OBJECT_FILES)
	mkdir -p $(@D)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $+

# BUILD RULES

$(LIBTRANSISTOR_HOME)/build/pthread/%.o: $(LIBTRANSISTOR_HOME)/pthread/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(WARNINGS) $(pthread_CC_FLAGS) -c -o $@ $<

# CLEAN RULES

.PHONY: clean_pthread

clean_pthread:
	rm -fr build/pthread
