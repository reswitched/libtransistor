include $(LIBTRANSISTOR_HOME)/libtransistor.mk

PROGRAM=pthread-test

CLEANUP_TYPE=C
#CLEANUP_TYPE=CPP

MUTEX_TEST_OBJS = \
  mutex1.o \
  mutex1e.o \
  mutex1n.o \
  mutex1r.o \
  mutex2.o \
  mutex2e.o \
  mutex2r.o \
  mutex3.o \
  mutex3e.o \
  mutex3r.o \
  mutex4.o \
  mutex5.o \
  mutex6.o \
  mutex6e.o \
  mutex6es.o \
  mutex6n.o \
  mutex6r.o \
  mutex6rs.o \
  mutex6s.o \
  mutex7.o \
  mutex7e.o \
  mutex7n.o \
  mutex7r.o \
  # Depends on unimplemented functions
  #mutex8.o \
  #mutex8e.o \
  #mutex8n.o \
  #mutex8r.o

MISC_OBJS = \
  main.o \
  test_main.o


MISC_TEST_OBJS = \
  valid1.o \
  valid2.o \
  self1.o \
  self2.o \
  equal1.o \
  count1.o \
  errno1.o \
  tsd1.o \
  tsd2.o \
  detach1.o
# Depends on non-portable functions
#  delay1.o \
#  delay2.o \
# Depends on unimplemented newlib functions
#  stress1.o \

#SEM_TEST_OBJS = \
#  semaphore1.o \
#  semaphore2.o \
#  semaphore3.o \
#  semaphore4.o \
#  semaphore4t.o \
#  semaphore5.o \
#  semaphore6.o

BARRIER_TEST_OBJS = \
  barrier1.o \
  barrier2.o \
  barrier3.o \
  barrier4.o \
  barrier5.o 

# Tests excluded because cancellation is not implemented
#  semaphore4.o 
#  semaphore4t.o 

THREAD_TEST_OBJS = \
  create1.o \
  create2.o \
  create3.o \
  join0.o \
  join1.o \
  join2.o \
  join3.o \
  join4.o \
  kill1.o \
  exit1.o \
  exit2.o \
  exit3.o \
  exit4.o \
  exit5.o \
# Depends on unimplemented HAL
#  once1.o \
#  once2.o \
#  once3.o \
#  once4.o \

# PTE specific behavior: thread reuse
#  reuse1.o \
#  reuse2.o \

# Not implemented yet
#  priority1.o \
#  priority2.o \
#  inherit1.o

SPIN_TEST_OBJS = \
  spin1.o \
  spin2.o \
  spin3.o \
# Depends on ftime
#  spin4.o

CONDVAR_TEST_OBJS = \
  condvar1.o \
# Needs NP method
#  condvar1_1.o \
#  condvar1_2.o \
# Needs ftime
#  condvar2.o \
#  condvar2_1.o \
#  condvar3.o \
#  condvar3_1.o \
#  condvar3_2.o \
#  condvar3_3.o \
#  condvar4.o \
#  condvar5.o \
#  condvar6.o \
#  condvar7.o \
#  condvar8.o \
#  condvar9.o 
#
RWLOCK_TEST_OBJS = \
  rwlock1.o \
# Needs ftime
#  rwlock2.o \
#  rwlock2_t.o \
#  rwlock3.o \
#  rwlock3_t.o \
#  rwlock4.o \
#  rwlock4_t.o \
#  rwlock5.o \
#  rwlock5_t.o \
#  rwlock6.o \
#  rwlock6_t.o \
#  rwlock6_t2.o \
#  rwlock7.o \
#  rwlock8.o

CANCEL_TEST_OBJS = \
  cancel1.o \
  cancel2.o \
  cancel3.o \
  cancel4.o \
  cancel5.o \
  cancel6a.o \
  cancel6d.o \
  cleanup0.o \
  cleanup1.o \
  cleanup2.o \
  cleanup3.o

BENCH_TEST_OBJS = \
  benchlib.o \
  benchtest1.o \
  benchtest2.o \
  benchtest3.o \
  benchtest4.o 

EXCEPTION_TEST_OBJS = \
  exception1.o \
  exception2.o \
  exception3.o

OBJS = $(MUTEX_TEST_OBJS) $(MISC_OBJS) $(MISC_TEST_OBJS) $(THREAD_TEST_OBJS) $(SEM_TEST_OBJS) $(BARRIER_TEST_OBJS) $(SPIN_TEST_OBJS) $(CONDVAR_TEST_OBJS) $(RWLOCK_TEST_OBJS) $(CANCEL_TEST_OBJS) #$(BENCH_TEST_OBJS) $(EXCEPTION_TEST_OBJS)

all: $(PROGRAM).nro

CFLAGS += -I../ -I../sys/switch
$(PROGRAM).nro.so: ${OBJS} $(LIBTRANSITOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	$(LD) $(LD_FLAGS) -o $@ ${OBJS} $(LIBTRANSISTOR_NRO_LDFLAGS)

clean:
	rm -f ${OBJS} $(PROGRAM).nro $(PROGRAM).nro.so

#CFLAGS = $(GLOBAL_CFLAGS) -O2 -Wall -g -I..  -fno-strict-aliasing  -I../.. -G0
#CXXFLAGS = $(CFLAGS) -fexceptions -fno-rtti
#ASFLAGS = $(CFLAGS)

#LDFLAGS = -L../..
#LIBS = -lc -lpthread-psp -lstdc++

#ifeq ($(CLEANUP_TYPE),CPPXX)
#
#LIBS += -lstdc++
#
#endif
#
#ifeq ($(CLEANUP_TYPE),CPPXXX)
#
#exception1.o: exception1.c
#	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) $(TARGET_ARCH) \
#	  -c ../../tests/exception1.c -o exception1.o
#
#exception2.o: exception2.c
#	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) $(TARGET_ARCH) \
#	  -c ../../tests/exception2.c -o exception2.o
#
#exception3.o: exception3.c
#	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) $(TARGET_ARCH) \
#	  -c ../../tests/exception3.c -o exception3.o
#endif
