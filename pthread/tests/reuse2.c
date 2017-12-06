/*
 * File: reuse2.c
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
 * - Test that thread reuse works for detached threads.
 * - Analyse thread struct reuse.
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
 * - This test is implementation specific
 * because it uses knowledge of internals that should be
 * opaque to an application.
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

#include "implement.h"

/*
 */

enum
{
  NUMTHREADS = 100
};


static int done = 0;

static void * func(void * arg)
{
  sched_yield();

  PTE_ATOMIC_INCREMENT(&done);

  return (void *) 0;
}

int pthread_test_reuse2()
{
  pthread_t t[NUMTHREADS];
  pthread_attr_t attr;
  int i;
  unsigned int notUnique = 0,
                           totalHandles = 0,
                                          reuseMax = 0,
                                                     reuseMin = NUMTHREADS;

  assert(pthread_attr_init(&attr) == 0);
  assert(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) == 0);

  for (i = 0; i < NUMTHREADS; i++)
    {
      assert(pthread_create(&t[i], &attr, func, NULL) == 0);
    }

  while (NUMTHREADS > PTE_ATOMIC_EXCHANGE_ADD(&done, 0L))
    phal_thread_sleep(100);

  phal_thread_sleep(100);

  /*
   * Analyse reuse by computing min and max number of times pthread_create()
   * returned the same pthread_t value.
   */
  for (i = 0; i < NUMTHREADS; i++)
    {
      if (t[i].p != NULL)
        {
          unsigned int j, thisMax;

          thisMax = t[i].x;

          for (j = i+1; j < NUMTHREADS; j++)
            if (t[i].p == t[j].p)
              {
                if (t[i].x == t[j].x)
                  notUnique++;
                if (thisMax < t[j].x)
                  thisMax = t[j].x;
                t[j].p = NULL;
              }

          if (reuseMin > thisMax)
            reuseMin = thisMax;

          if (reuseMax < thisMax)
            reuseMax = thisMax;
        }
    }

  for (i = 0; i < NUMTHREADS; i++)
    if (t[i].p != NULL)
      totalHandles++;

  /*
   * pthread_t reuse counts start at 0, so we need to add 1
   * to the max and min values derived above.
   */

  return 0;
}
