/*	$OpenBSD: rthread.c,v 1.6 2017/11/04 22:53:57 jca Exp $ */
/*
 * Copyright (c) 2004,2005 Ted Unangst <tedu@openbsd.org>
 * All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * The infrastructure of rthreads
 */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>

#include "phal.h"

#include "rthread.h"

#define RTHREAD_ENV_DEBUG	"RTHREAD_DEBUG"

int _rthread_debug_level;

static int _threads_inited;

struct pthread _initial_thread = {
	.flags_lock = _SPINLOCK_UNLOCKED,
	.name = "Original thread",
};

/*
 * internal support functions
 */

/*
 * Atomic lock for arm
 */

int
_atomic_lock(volatile _atomic_lock_t *lock)
{
	_atomic_lock_t old = 0;
	uint32_t scratch = 0;

	__asm__("1: ldaxr %w0, [%x1]       \n"
		"   stlxr %w2, %w3, [%x1]  \n"
		"   cmp %w2, #0            \n"
		"   bne 1b                 \n"
		"   dmb sy                 \n"
		: "+r" (old), "+r" (lock), "+r" (scratch)
		: "r" (_ATOMIC_LOCK_LOCKED));

	return (old != _ATOMIC_LOCK_UNLOCKED);
}

void
_spinlock(volatile _atomic_lock_t *lock)
{
	while (_atomic_lock(lock))
		sched_yield();
}

int
_spinlocktry(volatile _atomic_lock_t *lock)
{
	return 0 == _atomic_lock(lock);
}

void
_spinunlock(volatile _atomic_lock_t *lock)
{
	*lock = _ATOMIC_LOCK_UNLOCKED;
}

void
_rthread_internal_init(phal_tid maintid)
{
	pthread_t thread = &_initial_thread;
	//struct tib *tib;

	if (_threads_inited)
		return;

	thread->tib_tid = maintid;
	*phal_get_tls() = thread;

	thread->donesem.lock = _SPINLOCK_UNLOCKED;

	thread->tib_thread_flags = TIB_THREAD_INITIAL_STACK;

	/*
	 * Set the debug level from an environment string.
	 * Bogus values are silently ignored.
	 */
	// TODO: issetugid
	//if (! issetugid()) {
		char *envp = getenv(RTHREAD_ENV_DEBUG);

		if (envp != NULL) {
			char *rem;

			_rthread_debug_level = (int) strtol(envp, &rem, 0);
			if (*rem != '\0' || _rthread_debug_level < 0)
				_rthread_debug_level = 0;
		}
	//}

	_threads_inited = 1;
}

/*
 * real pthread functions
 */
pthread_t
pthread_self(void)
{
	if (__predict_false(!_threads_inited)) {
		char msg[] = "_rthread_internal_init not called";
		write(2, msg, strlen(msg));
		return NULL;
	}

	return *phal_get_tls();
}

void
pthread_exit(void *retval)
{
	struct rthread_cleanup_fn *clfn;
	pthread_t thread = pthread_self();

	if (thread->tib_cantcancel & CANCEL_DYING) {
		/*
		 * Called pthread_exit() from destructor or cancelation
		 * handler: blow up.  XXX write something to stderr?
		 */
		abort();
		//_exit(42);
	}

	thread->tib_cantcancel |= CANCEL_DYING;

	thread->retval = retval;

	for (clfn = thread->cleanup_fns; clfn; ) {
		struct rthread_cleanup_fn *oclfn = clfn;
		clfn = clfn->next;
		oclfn->fn(oclfn->arg);
		free(oclfn);
	}
	_rthread_tls_destructors(thread);
	_rthread_release(thread);

	phal_thread_exit(&thread->tib_tid);

	// We should never reach here.
	for(;;);
}

int
pthread_equal(pthread_t t1, pthread_t t2)
{
	return (t1 == t2);
}

