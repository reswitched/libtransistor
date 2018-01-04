/*
 * once4.c
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
 * Create several pthread_once objects and channel several threads
 * through each. Make the init_routine cancelable and cancel them
 * waiters waiting. Vary the priorities.
 *
 * Depends on API functions:
 *	pthread_once()
 *	pthread_create()
 *      pthread_testcancel()
 *      pthread_cancel()
 *      pthread_once()
 */

#include "test.h"

#define NUM_THREADS OS_MAX_SIMUL_THREADS / 5 /* Targeting each once control */
#define NUM_ONCE    5

static pthread_once_t o = PTHREAD_ONCE_INIT;
static pthread_once_t once[NUM_ONCE];

typedef struct
  {
    int i;
    int null;
    pte_osMutexHandle cs;
  } sharedInt_t;

static sharedInt_t numOnce = {0, 0};
static sharedInt_t numThreads = {0, 0};

typedef struct
  {
    int threadnum;
    int oncenum;
    int myPrio;
//  HANDLE w32Thread;
  } bag_t;

static bag_t threadbag[NUM_THREADS][NUM_ONCE];

//static CRITICAL_SECTION print_lock;

static void
mycleanupfunc(void * arg)
{

}

static void
myinitfunc(void)
{

  pte_osMutexLock(numOnce.cs);
  numOnce.i++;
  pte_osMutexUnlock(numOnce.cs);

  /* Simulate slow once routine so that following threads pile up behind it */
  phal_thread_sleep(10);
  /* test for cancelation late so we're sure to have waiters. */
  pthread_testcancel();
}

static void *
mythread(void * arg)
{
  bag_t * bag = (bag_t *) arg;
  struct sched_param param;

  /*
   * Cancel every thread. These threads are deferred cancelable only, so
   * only the thread performing the init_routine will see it (there are
   * no other cancelation points here). The result will be that every thread
   * eventually cancels only when it becomes the new initter.
   */
  pthread_t self = pthread_self();
//  bag->w32Thread = pthread_getw32threadhandle_np(self);
  /*
   * Set priority between -2 and 2 inclusive.
   */
  bag->myPrio = (bag->threadnum % 5) - 2;
  param.sched_priority = bag->myPrio;
  pthread_setschedparam(self, SCHED_OTHER, &param);

  /* Trigger a cancellation at the next cancellation point in this thread */
  pthread_cancel(self);
  pthread_cleanup_push(mycleanupfunc, arg);
  assert(pthread_once(&once[bag->oncenum], myinitfunc) == 0);
  pthread_cleanup_pop(1);

  pte_osMutexLock(numThreads.cs);
  numThreads.i++;
  pte_osMutexUnlock(numThreads.cs);
  return 0;
}

int pthread_test_once4()
{
  pthread_t t[NUM_THREADS][NUM_ONCE];
  int i, j;

  numOnce.i = 0;
  numThreads.i = 0;

//  pte_osMutexCreate(&print_lock);
//  pte_osMutexCreate(&numThreads.cs);
//  pte_osMutexCreate(&numOnce.cs);

  /*
   * Set the priority class to realtime - otherwise normal
   * Windows random priority boosting will obscure any problems.
   */
  //SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
  /* Set main thread to lower prio than threads */
  //SetThreadPriority(GetCurrentThread(), -2);

  for (j = 0; j < NUM_ONCE; j++)
    {
      once[j] = o;

      for (i = 0; i < NUM_THREADS; i++)
        {
          bag_t * bag = &threadbag[i][j];
          bag->threadnum = i;
          bag->oncenum = j;
          assert(pthread_create(&t[i][j], NULL, mythread, (void *) bag) == 0);
        }
    }

  for (j = 0; j < NUM_ONCE; j++)
    for (i = 0; i < NUM_THREADS; i++)
      if (pthread_join(t[i][j], NULL) != 0)
        assert(0);  //Join failed for [thread,once]

  /*
   * All threads will cancel, none will return normally from
   * pthread_once and so numThreads should never be incremented. However,
   * numOnce should be incremented by every thread (NUM_THREADS*NUM_ONCE).
   */
  assert(numOnce.i == NUM_ONCE * NUM_THREADS);
  assert(numThreads.i == 0);

//  pte_osMutexDelete(&numOnce.cs);
//  pte_osMutexDelete(&numThreads.cs);
//  pte_osMutexDelete(&print_lock);

  return 0;
}
