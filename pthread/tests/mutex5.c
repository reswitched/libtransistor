/*
 * mutex5.c
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
 * Confirm the equality/inequality of the various mutex types,
 * and the default not-set value.
 */

#include <stdio.h>
#include <stdlib.h>

#include "test.h"

static pthread_mutexattr_t mxAttr;

/* Prevent optimiser from removing dead or obvious asserts. */
int _optimiseFoil;
#define FOIL(x) (_optimiseFoil = x)

int
pthread_test_mutex5()
{
  int mxType = -1;

  assert(FOIL(PTHREAD_MUTEX_DEFAULT) == PTHREAD_MUTEX_NORMAL);
  assert(FOIL(PTHREAD_MUTEX_DEFAULT) != PTHREAD_MUTEX_ERRORCHECK);
  assert(FOIL(PTHREAD_MUTEX_DEFAULT) != PTHREAD_MUTEX_RECURSIVE);
  assert(FOIL(PTHREAD_MUTEX_RECURSIVE) != PTHREAD_MUTEX_ERRORCHECK);

  // No need for non-portable.
  /*assert(FOIL(PTHREAD_MUTEX_NORMAL) == PTHREAD_MUTEX_FAST_NP);
  assert(FOIL(PTHREAD_MUTEX_RECURSIVE) == PTHREAD_MUTEX_RECURSIVE_NP);
  assert(FOIL(PTHREAD_MUTEX_ERRORCHECK) == PTHREAD_MUTEX_ERRORCHECK_NP);*/

  assert(pthread_mutexattr_init(&mxAttr) == 0);
  assert(pthread_mutexattr_gettype(&mxAttr, &mxType) == 0);
  assert(mxType == PTHREAD_MUTEX_NORMAL);

  return 0;
}
