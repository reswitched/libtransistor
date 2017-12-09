/*
 * Test for pthread_detach().
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
 * Depends on API functions: pthread_create(), pthread_detach(), pthread_exit().
 */

#include "test.h"


enum
{
  NUMTHREADS = 20
};

static void *
func(void * arg)
{
  int i = (int) arg;

  phal_thread_sleep(i * 10);

  pthread_exit(arg);

  /* Never reached. */
  exit(1);

  /* Just to avoid compiler warnings */
  return NULL;
}

int pthread_test_detach1()
{
  pthread_t id[NUMTHREADS];
  int i;

  /* Create a few threads and then exit. */
  for (i = 0; i < NUMTHREADS; i++)
    {
      assert(pthread_create(&id[i], NULL, func, (void *) i) == 0);
    }


  /* Some threads will finish before they are detached, some after. */
  phal_thread_sleep(NUMTHREADS/2 * 10 + 50);

  for (i = 0; i < NUMTHREADS; i++)
    {
      assert(pthread_detach(id[i]) == 0);
    }

  phal_thread_sleep(NUMTHREADS * 10 + 1000);

  /*
   * Check that all threads are now invalid.
   * This relies on unique thread IDs - e.g. works with
   * pthreads-w32 or Solaris, but may not work for Linux, BSD etc.
   */
  for (i = 0; i < NUMTHREADS; i++)
    {
		// TODO: Add a way to check if a thread is still valid
      //assert(pthread_kill(id[i], 0) == ESRCH);
    }

  /* Success. */
  return 0;
}
