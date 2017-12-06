/*
 * File: exception1.c
 *
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-win32 - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999,2005 Pthreads-win32 contributors
 * 
 *      Contact Email: rpj@callisto.canberra.edu.au
 * 
 *      The current list of contributors is contained
 *      in the file CONTRIBUTORS included with the source
 *      code distribution. The list can also be seen at the
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
 * Test Synopsis: Test passing of exceptions back to the application.
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

#if defined(__cplusplus) && defined(PTE_SUPPORT_ASYNC_CANCEL)

/*
 * Create NUMTHREADS threads in addition to the Main thread.
 */
enum {
  NUMTHREADS = 4
};

static void *
exceptionedThread(void * arg)
{
  int dummy = 0;
  int result = ((int)PTHREAD_CANCELED + 1);
  /* Set to async cancelable */

  assert(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) == 0);

  assert(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL) == 0);

  phal_thread_sleep(100);

  try
  {
    /*
     * I had a zero divide exception here but it
     * wasn't being caught by the catch(...)
     * below under Mingw32. That could be a problem.
     */
    throw dummy;
  }
  catch (...)
  {
    /* Should get into here. */
    result = ((int)PTHREAD_CANCELED + 2);
  }

  return (void *) result;
}

static void *
canceledThread(void * arg)
{
  int result = ((int)PTHREAD_CANCELED + 1);
  int count;


  /* Set to async cancelable */

  assert(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) == 0);

  assert(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL) == 0);

  try
  {
    /*
     * We wait up to 10 seconds, waking every 0.1 seconds,
     * for a cancelation to be applied to us.
     */
    for (count = 0; count < 100; count++)
      phal_thread_sleep(100);
  }
  catch (...)
  {
    /* Should NOT get into here. */
    result = ((int)PTHREAD_CANCELED + 2);
  }

  return (void *) result;
}


int
pthread_test_exception1()
{
  int failed = 0;
  int i;
  pthread_t mt;
  pthread_t et[NUMTHREADS];
  pthread_t ct[NUMTHREADS];

  assert((mt = pthread_self()).p != NULL);

  for (i = 0; i < NUMTHREADS; i++)
    {
      assert(pthread_create(&et[i], NULL, exceptionedThread, (void *) 0) == 0);
      assert(pthread_create(&ct[i], NULL, canceledThread, NULL) == 0);
    }

  /*
   * Code to control or munipulate child threads should probably go here.
   */
  phal_thread_sleep(1000);

  for (i = 0; i < NUMTHREADS; i++)
    {
      assert(pthread_cancel(ct[i]) == 0);
    }

  /*
   * Give threads time to run.
   */
  phal_thread_sleep(NUMTHREADS * 1000);

  /*
   * Check any results here. Set "failed" and only print output on failure.
   */
  failed = 0;
  for (i = 0; i < NUMTHREADS; i++)
    {
      int fail = 0;
      int result = 0;

	/* Canceled thread */
      assert(pthread_join(ct[i], (void **) &result) == 0);
      assert(!(fail = (result != (int) PTHREAD_CANCELED)));

      failed = (failed || fail);

      /* Exceptioned thread */
      assert(pthread_join(et[i], (void **) &result) == 0);
      assert(!(fail = (result != ((int) PTHREAD_CANCELED + 2))));

      failed = (failed || fail);
    }

  assert(!failed);

  /*
   * Success.
   */
  return 0;
}

#else

int
pthread_test_exception1()
{
  printf("Test N/A for this compiler environment.\n");
  return 0;
}

#endif
