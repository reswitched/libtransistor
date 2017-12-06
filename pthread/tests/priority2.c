/*
 * File: priority2.c
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
 * --------------------------------------------------------------------------
 *
 * Test Synopsis:
 * - Test thread priority setting after creation.
 *
 * Test Method (Validation or Falsification):
 * -
 *
 * Requirements Tested:
 * -
 *
 * Features Tested:
 * -
 *
 * Cases Tested:
 * -
 *
 * Description:
 * -
 *
 * Environment:
 * -
 *
 * Input:
 * - None.
 *
 * Output:
 * - File name, Line number, and failed expression on failure.
 * - No output on success.
 *
 * Assumptions:
 * -
 *
 * Pass Criteria:
 * - Process returns zero exit status.
 *
 * Fail Criteria:
 * - Process returns non-zero exit status.
 */

#include "test.h"

enum
{
  PTW32TEST_THREAD_INIT_PRIO = 0,
  PTW32TEST_MAXPRIORITIES = 512
};

static pthread_barrier_t startBarrier, endBarrier;

static void * func(void * arg)
{
  int policy;
  int result;
  struct sched_param param;

  result = pthread_barrier_wait(&startBarrier);
  assert(result == 0 || result == PTHREAD_BARRIER_SERIAL_THREAD);
  assert(pthread_getschedparam(pthread_self(), &policy, &param) == 0);
  assert(policy == SCHED_OTHER);
  result = pthread_barrier_wait(&endBarrier);
  assert(result == 0 || result == PTHREAD_BARRIER_SERIAL_THREAD);

  assert(pte_osThreadGetPriority(pte_osThreadGetHandle()) == param.sched_priority);

  return (void *) param.sched_priority;
}



int pthread_test_priority2()
{
  pthread_t t;
  void * result = NULL;
  int result2;
  struct sched_param param;


  /*
    assert(pthread_create(&t, NULL, getValidPriorities, NULL) == 0);
    assert(pthread_join(t, &result) == 0);
  */

  assert(pthread_barrier_init(&startBarrier, NULL, 2) == 0);
  assert(pthread_barrier_init(&endBarrier, NULL, 2) == 0);

  /* Set the thread's priority to a known initial value.
   * If the new priority is invalid then the threads priority
   * is unchanged from the previous value.
   */
  /*
    SetThreadPriority(pthread_getw32threadhandle_np(pthread_self()),
                      PTW32TEST_THREAD_INIT_PRIO);
  */
  for (param.sched_priority = pte_osThreadGetMinPriority();
       param.sched_priority <= pte_osThreadGetMaxPriority();
       param.sched_priority++)
    {
      assert(pthread_create(&t, NULL, func, NULL) == 0);
      assert(pthread_setschedparam(t, SCHED_OTHER, &param) == 0);
      result2 = pthread_barrier_wait(&startBarrier);
      assert(result2 == 0 || result2 == PTHREAD_BARRIER_SERIAL_THREAD);
      result2 = pthread_barrier_wait(&endBarrier);
      assert(result2 == 0 || result2 == PTHREAD_BARRIER_SERIAL_THREAD);

//      assert(GetThreadPriority(pthread_getw32threadhandle_np(t)) ==
//	  validPriorities[param.sched_priority+(PTW32TEST_MAXPRIORITIES/2)]);

      pthread_join(t, &result);
      assert(param.sched_priority == (int)result);
    }

  assert(pthread_barrier_destroy(&startBarrier) == 0);
  assert(pthread_barrier_destroy(&endBarrier) == 0);

  return 0;
}
