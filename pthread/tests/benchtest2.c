/*
 * benchtest1.c
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
 * Measure time taken to complete an elementary operation.
 *
 * - Mutex
 *   Two threads iterate over lock/unlock for each mutex type.
 *   The two threads are forced into lock-step using two mutexes,
 *   forcing the threads to block on each lock operation. The
 *   time measured is therefore the worst case senario.
 */

#include "test.h"


#ifdef __GNUC__
#include <stdlib.h>
#endif

#include "benchtest.h"

#define PTW32_MUTEX_TYPES
#define ITERATIONS      10000L

static pthread_mutex_t gate1, gate2;
static pthread_mutexattr_t ma;
static long durationMilliSecs;
static long overHeadMilliSecs = 0;
static struct _timeb currSysTimeStart;
static struct _timeb currSysTimeStop;
static pthread_t worker;
static int running = 0;

#define GetDurationMilliSecs(_TStart, _TStop) ((_TStop.time*1000+_TStop.millitm) \
                                               - (_TStart.time*1000+_TStart.millitm))

/*
 * Dummy use of j, otherwise the loop may be removed by the optimiser
 * when doing the overhead timing with an empty loop.
 */
#define TESTSTART \
  { int i, j = 0, k = 0; _ftime(&currSysTimeStart); for (i = 0; i < ITERATIONS; i++) { j++;

#define TESTSTOP \
  }; _ftime(&currSysTimeStop); if (j + k == i) j++; }


static void *
overheadThread(void * arg)
{
  do
    {
      sched_yield();
    }
  while (running);

  return NULL;
}


static void *
workerThread(void * arg)
{
  do
    {
      (void) pthread_mutex_lock(&gate1);
      (void) pthread_mutex_lock(&gate2);
      (void) pthread_mutex_unlock(&gate1);
      sched_yield();
      (void) pthread_mutex_unlock(&gate2);
    }
  while (running);

  return NULL;
}

static void
runTest (char * testNameString, int mType)
{
#ifdef PTW32_MUTEX_TYPES
  assert(pthread_mutexattr_settype(&ma, mType) == 0);
#endif
  assert(pthread_mutex_init(&gate1, &ma) == 0);
  assert(pthread_mutex_init(&gate2, &ma) == 0);
  assert(pthread_mutex_lock(&gate1) == 0);
  assert(pthread_mutex_lock(&gate2) == 0);
  running = 1;
  assert(pthread_create(&worker, NULL, workerThread, NULL) == 0);
  TESTSTART
  (void) pthread_mutex_unlock(&gate1);
  sched_yield();
  (void) pthread_mutex_unlock(&gate2);
  (void) pthread_mutex_lock(&gate1);
  (void) pthread_mutex_lock(&gate2);
  TESTSTOP
  running = 0;
  assert(pthread_mutex_unlock(&gate2) == 0);
  assert(pthread_mutex_unlock(&gate1) == 0);
  assert(pthread_join(worker, NULL) == 0);
  assert(pthread_mutex_destroy(&gate2) == 0);
  assert(pthread_mutex_destroy(&gate1) == 0);
  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;
  printf( "%-45s %15ld %15.3f\n",
          testNameString,
          durationMilliSecs,
          (float) durationMilliSecs * 1E3 / ITERATIONS / 4   /* Four locks/unlocks per iteration */);
}


int pthread_test_bench2()
{
  assert(pthread_mutexattr_init(&ma) == 0);

  printf( "=============================================================================\n");
  printf( "\nLock plus unlock on a locked mutex.\n");
  printf("%ld iterations, four locks/unlocks per iteration.\n\n", ITERATIONS);

  printf( "%-45s %15s %15s\n",
          "Test",
          "Total(msec)",
          "average(usec)");

  /*
   * Time the loop overhead so we can subtract it from the actual test times.
   */

  running = 1;
  assert(pthread_create(&worker, NULL, overheadThread, NULL) == 0);
  TESTSTART
  sched_yield();
  sched_yield();
  TESTSTOP
  running = 0;
  assert(pthread_join(worker, NULL) == 0);
  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;
  overHeadMilliSecs = durationMilliSecs;


  /*
   * Now we can start the actual tests
   */
#ifdef PTW32_MUTEX_TYPES
  runTest("PTHREAD_MUTEX_DEFAULT", PTHREAD_MUTEX_DEFAULT);

  runTest("PTHREAD_MUTEX_NORMAL", PTHREAD_MUTEX_NORMAL);

  runTest("PTHREAD_MUTEX_ERRORCHECK", PTHREAD_MUTEX_ERRORCHECK);

  runTest("PTHREAD_MUTEX_RECURSIVE", PTHREAD_MUTEX_RECURSIVE);
#else
  runTest("Blocking locks", 0);
#endif

  printf( "=============================================================================\n");
  /*
   * End of tests.
   */

  pthread_mutexattr_destroy(&ma);

  return 0;
}
