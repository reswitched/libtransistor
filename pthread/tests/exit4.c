/*
 * File: exit4.c
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
 * Test Synopsis: Test calling pthread_exit from a Win32 thread
 *                without having created an implicit POSIX handle for it.
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
 * - have working pthread_create, pthread_self, pthread_mutex_lock/unlock
 *   pthread_testcancel, pthread_cancel, pthread_join
 *
 * Pass Criteria:
 * - Process returns zero exit status.
 *
 * Fail Criteria:
 * - Process returns non-zero exit status.
 */

#include "test.h"



/*
 * Create NUMTHREADS threads in addition to the Main thread.
 */
enum
{
  NUMTHREADS = 5
};

typedef struct bag_t_ bag_t;
struct bag_t_
  {
    int threadnum;
    int started;
    /* Add more per-thread state variables here */
    int count;
  };

static bag_t threadbag[NUMTHREADS + 1];


static int osThread(void * arg)
{
  int result = 1;
  bag_t * bag = *((bag_t **) arg);

  assert(bag == &threadbag[bag->threadnum]);
  assert(bag->started == 0);
  bag->started = 1;

  /*
   * Doesn't return and doesn't create an implicit POSIX handle.
   */
  pthread_exit((void *) result);

  return 0;
}



int pthread_test_exit4()
{
  int failed = 0;
  int i;
  phal_tid h[NUMTHREADS + 1];

  for (i = 1; i <= NUMTHREADS; i++)
    {
      void *ptr;

      /*
        char threadName[32];
      	snprintf(threadName, sizeof(threadName), "test_th%d", i);
      */

      threadbag[i].started = 0;
      threadbag[i].threadnum = i;

      ptr = &(threadbag[i]);

      phal_thread_create(&h[i], osThread, ptr);

    }

  /*
   * Code to control or munipulate child threads should probably go here.
   */
  phal_thread_sleep(500);

  /*
   * Give threads time to run.
   */
  phal_thread_sleep(NUMTHREADS * 100);

  /*
   * Standard check that all threads started.
   */
  for (i = 1; i <= NUMTHREADS; i++)
    {
      if (!threadbag[i].started)
        {
          failed |= !threadbag[i].started;
        }
    }

  assert(!failed);

  /*
   * Check any results here. Set "failed" and only print output on failure.
   */
  failed = 0;
  for (i = 1; i <= NUMTHREADS; i++)
    {
      int fail = 0;
      int result = 0;

      /*
       * Can't get a result code.
       */
      result = 1;

      fail = (result != 1);

      failed = (failed || fail);
    }

  assert(!failed);

  /*
   * Success.
   */
  return 0;
}

