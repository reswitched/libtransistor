/*
 * Test for pthread_join() returning return value from threads.
 *
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-embedded (PTE) - POSIX Threads Library for embedded systems
 *      Copyright(C) 2008 Jason Schmidlapp
 *
 *      Contact Email: jschmidlapp@users.sourceforge.net
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
 * Verifies that pthread_join can be cancelled.
 */

#include "test.h"

static pthread_t handle1;
static pthread_t handle2;

static int thread2_status;

static void *
thr1(void * arg)
{
  phal_thread_sleep(5000);

  return NULL;
}

static void *
thr2(void * arg)
{
  int result;

  assert(pthread_join(handle1,NULL) == 0);

  thread2_status = 1;

  return NULL;
}

int pthread_test_join4()
{
  thread2_status = 0;

  assert(pthread_create(&handle1, NULL, thr1, NULL) == 0);
  assert(pthread_create(&handle2, NULL, thr2, NULL) == 0);

  /* Give some time for thread #1 to start sleeping and thread #2 to wait on thread #1 */
  phal_thread_sleep(500);

  /* Cancel thread #2 (who is waiting on thread #1) */
  assert(pthread_cancel(handle2) == 0);
  
  /* Wait a short amount of time for cancellation to take effect */
  phal_thread_sleep(500);

  /* Make sure that pthread_join exited after cancellation */
  assert(thread2_status == 1);
  
  assert(pthread_join(handle1, NULL) == 0);
  assert(pthread_join(handle2, NULL) == 0);

  /* Success. */
  return 0;
}
