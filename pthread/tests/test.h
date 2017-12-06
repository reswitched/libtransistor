/*
 * test.h
 *
 * Useful definitions and declarations for tests.
 *
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-embedded (PTE) - POSIX Threads Library for embedded systems
 *      Copyright(C) 2008 Jason Schmidlapp
 *
 *      Contact Email: jschmidlapp@users.sourceforge.net
 *
 *
 *      Based upon Pthreads-win32 - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999,2005 Pthreads-win32 contributors
 *
 *      Contact Email: rpj@callisto.canberra.edu.au
 *
 *      The original list of contributors to the Pthreads-win32 project
 *      is contained in the file CONTRIBUTORS.ptw32 included with the
 *      source code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      http://sources.redhat.com/pthreads-win32/contributors.html
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 *
 */

#ifndef _PTHREAD_TEST_H_
#define _PTHREAD_TEST_H_

#include <stdio.h>
#include <stdlib.h>

#include "phal.h"

#include "pthread.h"
#include "sched.h"
#include <errno.h>
//#include "semaphore.h"

//#include <windows.h>


#define PTW32_THREAD_NULL_ID {NULL,0}

#if defined(__MINGW32__)
#include <stdint.h>
#elif defined(__BORLANDC__)
#define int64_t ULONGLONG
#else
#define int64_t _int64
#endif

extern const char * error_string;


/*
 * The Mingw32 assert macro calls the CRTDLL _assert function
 * which pops up a dialog. We want to run in batch mode so
 * we define our own assert macro.
 */
#ifdef assert
# undef assert
#endif

#ifndef ASSERT_TRACE
# define ASSERT_TRACE 0
#else
# undef ASSERT_TRACE
# define ASSERT_TRACE 1
#endif

# define assert(e) \
   ((e) ? ((ASSERT_TRACE) ? fprintf(stdout, \
                                    "Assertion succeeded: (%s), file %s, line %d\n", \
			            #e, __FILE__, (int) __LINE__), \
	                            fflush(stdout) : \
                             0) : \
          (fprintf(stderr, "Assertion failed: (%s), file %s, line %d\n", \
                   #e, __FILE__, (int) __LINE__), exit(1), 0))

extern int assertE;
# define assert_e(e, o, r) \
   (((assertE = e) o (r)) ? ((ASSERT_TRACE) ? fprintf(stdout, \
                                    "Assertion succeeded: (%s), file %s, line %d\n", \
			            #e, __FILE__, (int) __LINE__), \
	                            fflush(stdout) : \
                             0) : \
          (fprintf(stderr, "Assertion failed: (%s %s %s), file %s, line %d, error %s\n", \
                   #e,#o,#r, __FILE__, (int) __LINE__, error_string[assertE]), exit(1), 0))

#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


int pthread_test_mutex1();
int pthread_test_mutex1e();
int pthread_test_mutex1n();
int pthread_test_mutex1r();

int pthread_test_mutex2();
int pthread_test_mutex2e();
int pthread_test_mutex2r();

int pthread_test_mutex3();
int pthread_test_mutex3e();
int pthread_test_mutex3r();

int pthread_test_mutex4();

int pthread_test_mutex5();

int pthread_test_mutex6();
int pthread_test_mutex6e();
int pthread_test_mutex6es();
int pthread_test_mutex6n();
int pthread_test_mutex6r();
int pthread_test_mutex6rs();
int pthread_test_mutex6s();

int pthread_test_mutex7();
int pthread_test_mutex7e();
int pthread_test_mutex7n();
int pthread_test_mutex7r();

int pthread_test_mutex8();
int pthread_test_mutex8e();
int pthread_test_mutex8n();
int pthread_test_mutex8r();

int pthread_test_valid1();
int pthread_test_valid2();

int pthread_test_self1();
int pthread_test_self2();

int pthread_test_equal1();

int pthread_test_create1();
int pthread_test_create2();
int pthread_test_create3();

int pthread_test_semaphore1();
int pthread_test_semaphore2();
int pthread_test_semaphore3();
int pthread_test_semaphore4();
int pthread_test_semaphore4t();
int pthread_test_semaphore5();
int pthread_test_semaphore6();

int pthread_test_barrier1();
int pthread_test_barrier2();
int pthread_test_barrier3();
int pthread_test_barrier4();
int pthread_test_barrier5();

int pthread_test_count1();

int pthread_test_create1();
int pthread_test_create2();
int pthread_test_create3();

int pthread_test_delay1();
int pthread_test_delay2();

int pthread_test_errno1();

int pthread_test_join0();
int pthread_test_join1();
int pthread_test_join2();
int pthread_test_join3();
int pthread_test_join4();

int pthread_test_kill1();

int pthread_test_once1();
int pthread_test_once2();
int pthread_test_once3();
int pthread_test_once4();

int pthread_test_spin1();
int pthread_test_spin2();
int pthread_test_spin3();
int pthread_test_spin4();

int pthread_test_tsd1();
int pthread_test_tsd2();

int pthread_test_condvar1_1();
int pthread_test_condvar1_2();
int pthread_test_condvar1();
int pthread_test_condvar2_1();
int pthread_test_condvar2();
int pthread_test_condvar3();
int pthread_test_condvar3_1();
int pthread_test_condvar3_2();
int pthread_test_condvar3_3();
int pthread_test_condvar4();
int pthread_test_condvar5();
int pthread_test_condvar6();
int pthread_test_condvar7();
int pthread_test_condvar8();
int pthread_test_condvar9();

int pthread_test_stress1();

int pthread_test_detach1();

int pthread_test_exit1();
int pthread_test_exit2();
int pthread_test_exit3();
int pthread_test_exit4();
int pthread_test_exit5();

int pthread_test_reuse1();
int pthread_test_reuse2();

int pthread_test_rwlock1();
int pthread_test_rwlock2();
int pthread_test_rwlock2t();
int pthread_test_rwlock3();
int pthread_test_rwlock3t();
int pthread_test_rwlock4();
int pthread_test_rwlock4t();
int pthread_test_rwlock5();
int pthread_test_rwlock5t();
int pthread_test_rwlock6();
int pthread_test_rwlock6t();
int pthread_test_rwlock6t2();
int pthread_test_rwlock7();
int pthread_test_rwlock8();

int pthread_test_priority1();
int pthread_test_priority2();

int pthread_test_inherit1();

int pthread_test_cancel1();
int pthread_test_cancel2();
int pthread_test_cancel3();
int pthread_test_cancel4();
int pthread_test_cancel5();
int pthread_test_cancel6a();
int pthread_test_cancel6d();
int pthread_test_cancel7();
int pthread_test_cancel8();
int pthread_test_cancel9();

int pthread_test_cleanup0();
int pthread_test_cleanup1();
int pthread_test_cleanup2();
int pthread_test_cleanup3();

int pthread_test_bench1();
int pthread_test_bench2();
int pthread_test_bench3();
int pthread_test_bench4();

int pthread_test_exception1();
int pthread_test_exception2();
int pthread_test_exception3();

#ifdef __cplusplus
}
#endif /* __cplusplus */
