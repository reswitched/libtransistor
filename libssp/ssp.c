/* Stack protector support.
	 Copyright (C) 2005-2017 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file into combinations with other programs,
and to distribute those combinations without any restriction coming
from the use of this file.  (The General Public License restrictions
do apply in other respects; for example, they cover modification of
the file, and distribution when not linked into a combine
executable.)

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */


#include <stdio.h>
#include <unistd.h>

void *__stack_chk_guard = 0;

void __guard_setup(void)
{
	unsigned char *p;

	if (__stack_chk_guard != 0)
	{
		return;
	}

	// If a random generator can't be used, the protector switches the guard
	//	 to the "terminator canary".
	p = (unsigned char *)&__stack_chk_guard;
	p[sizeof(__stack_chk_guard)-1] = 255;
	p[sizeof(__stack_chk_guard)-2] = '\n';
	p[0] = 0;
}

static void fail(const char *msg1, const char *msg2)
{
	// Print error message directly to the tty. This avoids Bad Things
	//   happening if stderr is redirected.
	printf("%s", msg1);

#ifdef __GNU_LIBRARY__
	extern char *__progname;
	printf("%s terminated", __progname);
#else
	printf("%s", msg2);
#endif

	// Try very hard to exit.  Note that signals may be blocked preventing
	//   the first two options from working.  The use of volatile is here to
	//   prevent optimizers from "knowing" that __builtin_trap is called first,
	//   and that it doesn't return, and so "obviously" the rest of the code
	//   is dead.
	_exit(134);
}

void (*guard)(void) __attribute__((section (".ctors"))) = __guard_setup;

void __stack_chk_fail(void)
{
	fail("*** stack smashing detected ***: ", "stack smashing detected: terminated");
}

void __chk_fail(void)
{
	fail("*** buffer overflow detected ***: ", "buffer overflow detected: terminated");
}
