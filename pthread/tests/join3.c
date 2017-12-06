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
 * Depends on API functions: pthread_create().
 */

#include "test.h"

static void *
func(void * arg)
{
	// TODO: sched_yield
  //sched_yield();
  phal_thread_sleep(0);
  return arg;
}

int pthread_test_join3()
{
  pthread_t id[4];
  int i;
  int result;

  /* Create a few threads and then exit. */
  for (i = 0; i < 4; i++)
    {
      assert(pthread_create(&id[i], NULL, func, (void *) i) == 0);
    }

  /*
   * Let threads exit before we join them.
   * We should still retrieve the exit code for the threads.
   */
  phal_thread_sleep(1000);

  for (i = 0; i < 4; i++)
    {
      assert(pthread_join(id[i], (void **) &result) == 0);
      assert(result == i);
    }

  /* Success. */
  return 0;
}
