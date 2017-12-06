/*
 * spin4.c
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
 * Declare a static spinlock object, lock it, spin on it,
 * and then unlock it again.
 */

#include "test.h"

static pthread_spinlock_t lock = PTHREAD_SPINLOCK_INITIALIZER;
static struct _timeb currSysTimeStart;
static struct _timeb currSysTimeStop;

#define GetDurationMilliSecs(_TStart, _TStop) ((_TStop.time*1000+_TStop.millitm) \
					       - (_TStart.time*1000+_TStart.millitm))

static int washere = 0;

static void * func(void * arg)
{
  _ftime(&currSysTimeStart);
  washere = 1;
  assert(pthread_spin_lock(&lock) == 0);
  assert(pthread_spin_unlock(&lock) == 0);
  _ftime(&currSysTimeStop);

  return (void *) GetDurationMilliSecs(currSysTimeStart, currSysTimeStop);
}

int pthread_test_spin4()
{
  long result = 0;
  pthread_t t;
  struct _timeb sysTime;

  if (pthread_num_processors_np() == 1)
    {
      printf("spin test #4 not run - it requires multiple CPUs.\n");
      return 0;
    }

  assert(pthread_spin_lock(&lock) == 0);

  assert(pthread_create(&t, NULL, func, NULL) == 0);

  while (washere == 0)
    {
      sched_yield();
    }

  do
    {
      sched_yield();
      _ftime(&sysTime);
    }
  while (GetDurationMilliSecs(currSysTimeStart, sysTime) <= 1000);

  assert(pthread_spin_unlock(&lock) == 0);

  assert(pthread_join(t, (void **) &result) == 0);
  assert(result > 1000);

  assert(pthread_spin_destroy(&lock) == 0);

  assert(washere == 1);

  return 0;
}
