/*
 * File: semaphore5.c
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
 * Test Synopsis: Verifies that sem_timedwait doesn't return before timeout 
 *                expires 
 * -
 *
 * Test Method (Validation or Falsification):
 * - Validation
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

static sem_t s;
static int semStatus;

static void *
thr (void * arg)
{
  struct timespec abstime =
    {
      0, 0
    };
  struct timeval currSysTime;
  const long long NANOSEC_PER_MILLISEC = 1000000;

  gettimeofday(&currSysTime, NULL);

  abstime.tv_sec = currSysTime.tv_sec;
  abstime.tv_nsec = NANOSEC_PER_MILLISEC * currSysTime.tv_usec / 1000;

  abstime.tv_sec += 5;
  assert(sem_timedwait(&s, &abstime) == -1);
  assert(errno == ETIMEDOUT);

  semStatus = 1;
  //  assert(pthread_detach(pthread_self()) == 0);
  return NULL;
}

int pthread_test_semaphore6(void)
{
  int value = 0;
  pthread_t handle;

  assert(sem_init(&s, PTHREAD_PROCESS_PRIVATE, 0) == 0);
  assert(sem_getvalue(&s, &value) == 0);
  assert(value == 0);

  semStatus = 0;

  assert(pthread_create(&handle, NULL, thr, NULL) == 0);

  phal_thread_sleep(3000);

  /* Make sure that sem_timedwait doesn't return too early */
  assert(semStatus == 0);

  assert(pthread_join(handle, NULL) == 0);

  assert(sem_destroy(&s) == 0);

  return 0;
}

