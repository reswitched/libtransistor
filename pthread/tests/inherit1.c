/*
 * File: inherit1.c
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
 * - Test thread priority inheritance.
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

static void * func(void * arg)
{
  int policy;
  struct sched_param param;

  assert(pthread_getschedparam(pthread_self(), &policy, &param) == 0);

  return (void *) param.sched_priority;
}

int pthread_test_inherit1()
{
  pthread_t t;
  pthread_t mainThread = pthread_self();
  pthread_attr_t attr;
  int result = 0;
  struct sched_param param;
  struct sched_param mainParam;
  int prio;
  int policy;
  int inheritsched = -1;

  assert(pthread_attr_init(&attr) == 0);
  assert(pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED) == 0);
  assert(pthread_attr_getinheritsched(&attr, &inheritsched) == 0);
  assert(inheritsched == PTHREAD_INHERIT_SCHED);

  for (prio = pte_osThreadGetMinPriority();
       prio <= pte_osThreadGetMaxPriority();
       prio++)
    {
      mainParam.sched_priority = prio;

      /* Change the main thread priority */
      assert(pthread_setschedparam(mainThread, SCHED_OTHER, &mainParam) == 0);
      assert(pthread_getschedparam(mainThread, &policy, &mainParam) == 0);
      assert(policy == SCHED_OTHER);
      /* Priority returned below should be the level set by pthread_setschedparam(). */
      assert(mainParam.sched_priority == prio);

      pte_osThreadSetPriority(pte_osThreadGetHandle(), prio);

      assert(pte_osThreadGetPriority(pte_osThreadGetHandle()) == prio);

      for (param.sched_priority = prio;
           param.sched_priority <= pte_osThreadGetMaxPriority();
           param.sched_priority++)
        {
          /* The new thread create should ignore this new priority */
          assert(pthread_attr_setschedparam(&attr, &param) == 0);
          assert(pthread_create(&t, &attr, func, NULL) == 0);
          pthread_join(t, (void **)&result);
          assert((int) result == mainParam.sched_priority);
        }
    }

  return 0;
}
