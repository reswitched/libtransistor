#ifndef LINUX
#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"
#include "ini.h"

static const char *ibuf; // entire INI here
static const char *xbuf; // INI buffer ending

static const char *sbuf; // search start pointer
static const char *ebuf; // search end pointer

static char inival[64];

void I_Init(const char *buf, int size)
{
	sbuf = buf;
	ibuf = buf;
	xbuf = buf + size;
	ebuf = buf + size;
}

const char *I_GetValue(const char *var)
{
	const char *src = sbuf;
	int len;

	// locate variable
	len = strlen(var);
	while(src + len <= ebuf-2)
	{
		if(src[len] == '=' && !strncmp(src, var, len))
		{
			// found
			char *dst = inival;
			//copy value
			src += len + 1;
			while(src != ebuf && *src != '\n' && *src != '\r' && dst != inival + sizeof(inival) - 1)
			{
				*dst = *src;
				dst++;
				src++;
			}
			*dst = 0;
			// and return it
			return inival;
		}
		// skip to next line
		while(src != ebuf && *src != '\n' && *src != '\r')
			src++;
		src++;
	}

	return NULL;
}

int I_GetSection(const char *sec, int num)
{
	const char *src = ibuf;
	int len;
	int state = 0;

	sbuf = ibuf;
	ebuf = xbuf;

	// locate correct section
	len = strlen(sec);
	while(src != ebuf)
	{
		// check for section
		if(*src == '[')
		{
			if(state)
			{
				// got next section
				ebuf = src - 1;
				return 1;
			}
			src++;
			if(src + len >= ebuf)
				// EOF
				return 0;
			if(src[len] == ']' && !strncmp(src, sec, len))
			{
				// found section
				if(!num)
				{
					// it is requested one
					sbuf = src + len + 1;
					// find next section, if any
					state = 1;
				} else
					// it is not requested one
					num--;
			}
		}
		// skip to next line
		while(src != ebuf && *src != '\n' && *src != '\r')
			src++;
		src++;
	}
	return state;
}

const char *I_GetValueFull(const char *var, const char *sec)
{
	if(!I_GetSection(sec, 0))
		return NULL;
	return I_GetValue(var);
}

