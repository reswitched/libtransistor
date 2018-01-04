/*
 * File: condvar1_1.c
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
 * - Test CV linked list management.
 *
 * Test Method (Validation or Falsification):
 * - Validation:
 *   Initiate and destroy several CVs in random order.
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
 * - Creates and then imediately destroys a CV. Does not
 *   test the CV.
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
 * - All initialised CVs destroyed without segfault.
 * - Successfully broadcasts all remaining CVs after
 *   each CV is removed.
 *
 * Fail Criteria:
 */

#include <stdlib.h>
#include "test.h"

enum
{
  NUM_CV = 10
};

static pthread_cond_t cv[NUM_CV];

int pthread_test_condvar1_1()
{
  int i, j;

  for (i = 0; i < NUM_CV; i++)
    {
      /* Traverse the list before every init of a CV. */
      assert(pthread_timechange_handler_np(NULL) == (void *) 0);
      assert(pthread_cond_init(&cv[i], NULL) == 0);
    }

  j = NUM_CV;
  (void) srand((unsigned)time(NULL));

  do
    {
      i = rand() % NUM_CV;

      if (cv[i] != NULL)
        {
          j--;
          assert(pthread_cond_destroy(&cv[i]) == 0);
          /* Traverse the list every time we remove a CV. */
          assert(pthread_timechange_handler_np(NULL) == (void *) 0);
        }
    }
  while (j > 0);

  return 0;
}
