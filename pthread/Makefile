#	$OpenBSD: Makefile,v 1.49 2017/10/15 23:40:33 guenther Exp $

NAME=libpthread.a

#CFLAGS+=-Wall -g -Werror -Wshadow
#CFLAGS+=-Werror-implicit-function-declaration
#CFLAGS+=-Wsign-compare
CC_FLAGS+=-Isys/switch/ -I.

LDADD = -Wl,-znodelete 
SRCS=	rthread_attr.c \
	rthread_barrier.c \
	rthread_barrier_attr.c \
	rthread_cond.c \
	rthread_condattr.c \
	rthread_debug.c \
	rthread_getcpuclockid.c \
	rthread_internal.c \
	rthread_mutex.c \
	rthread_mutex_prio.c \
	rthread_mutexattr.c \
	rthread_once.c \
	rthread_rwlock.c \
	rthread_rwlockattr.c \
	rthread_sched.c \
	rthread_sem.c \
	rthread_sig.c \
	rthread_spin_lock.c \
	rthread_thread.c \
	rthread_tls.c \
	sched_prio.c \
	sys/switch/phal.c
	#rthread_stack.c \
	#rthread_file.c \
	#rthread_libc.c \
	# Seems to be an alternative implementation of mutex ?
	#rthread_sync.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(NAME)
