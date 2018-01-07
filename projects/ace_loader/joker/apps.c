#ifndef LINUX
#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#else
#include <dirent.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"
#include "system.h"
#include "gfx.h"
#include "apps.h"
#include "ini.h"

static const char *const opt_names[NUM_OPTION_TYPES] =
{
	"enum",
	"enum2",
	"boolean"
};

static int numapps;
static char tmpath[64];
char filetmp[96*1024]; // BMP icon must fit in here

app_t apps[MAXAPPS];

static int A_AddNew(const char *path)
{
	int i, cur, type, numval;
	const char *temp;
	option_t **opt;
	int pathlen = strlen(path);

	if(pathlen >= APP_MAXPATH - 5)
		return 0;

	sprintf(tmpath, "%s/app.ini", path);

	i = S_ReadFile(tmpath, filetmp, sizeof(filetmp));
	if(i <= 0)
	{
		printf("- failed to read '%s' %i\n", tmpath, -i);
		return 0;
	}

	I_Init(filetmp, i);
	if(!I_GetSection("app", 0))
		return 0;

	// app name
	temp = I_GetValue("title");
	if(!temp)
		return 0;
	strncpy(apps[numapps].name, temp, APP_MAXNAME-1);
	apps[numapps].name[APP_MAXNAME-1] = 0;

	// app NRO
	temp = I_GetValue("nro");
	if(!temp)
		return 0;
	snprintf(apps[numapps].path, APP_MAXPATH-1, "%s/%s", path, temp);
	apps[numapps].path[APP_MAXPATH-1] = 0;

	// version
	temp = I_GetValue("version");
	if(temp)
	{
		strncpy(apps[numapps].info, temp, APP_MAXINFO-1);
	} else
		apps[numapps].info[0] = 0;
	apps[numapps].info[APP_MAXINFO-1] = 0;

	// author
	temp = I_GetValue("author");
	if(temp)
	{
		int l = strlen(apps[numapps].info);
		if(!l)
			strncpy(apps[numapps].info, temp, APP_MAXINFO-1);
		else
		if(l < 25)
			snprintf(apps[numapps].info + l, (APP_MAXINFO-1) - l, "  |  %s", temp);
	}

	// options
	// loop trough all [opion] sections in INI
	opt = &apps[numapps].options;
	for(i = 0, cur = 0; cur < MAXOPTIONS; i++)
	{
		int j, size;
		char *dst;
		option_t *new = NULL;

		*opt = NULL;
		if(!I_GetSection("option", i))
			break;

		temp = I_GetValue("type");
		if(!temp)
			break;

		for(type = 0; type < NUM_OPTION_TYPES; type++)
			if(!strcmp(opt_names[type], temp))
				break;
		if(type == NUM_OPTION_TYPES)
			// unknown type; ignore
			continue;

		// calculate suboptions size
		// loop trough all 'valueX' variables in INI
		// allocate memory for 'option_t' and all the suboptions names + 0xFF terminator
		// then add optional 'parameter'
		// then add all 'paramX' same way as 'valueX'

		// add every 'valueX'
		size = 0;
		numval = 0;
		for(numval = 0; numval < MAXOPTIONS; numval++)
		{
			sprintf(tmpath, "value%i", numval);
			temp = I_GetValue(tmpath);
			if(!temp)
				break;
			size += strlen(temp) + 1;
		}
		// check
		if(!size)
			// this option have no values; ignore
			continue;
		size++; // 0xFF suboptions terminator

		// add 'parameter'
		temp = I_GetValue("parameter");
		if(temp)
			size += strlen(temp);
		size++; // NUL terminator

		// add every 'paramX'
		for(j = 0; j < numval; j++)
		{
			sprintf(tmpath, "param%i", j);
			temp = I_GetValue(tmpath);
			if(temp)
				size += strlen(temp);
			size++; // NUL
		}

		// allocate memory
		new = S_GetMemory(sizeof(option_t) + size);
		if(!new)
			// out of memory
			break;
		// set type
		new->type = type;
		// reset position
		new->choice = 0;
		// reset selection
		switch(type)
		{
			case OPTYPE_ENUM0:
				// first one selected
				new->value = 1;
			break;
			default:
				// none selected
				new->value = 0;
			break;
		}
		// get name
		temp = I_GetValue("title");
		if(!temp)
		{
			sprintf(tmpath, "Option %i", i);
			temp = tmpath;
		}
		strncpy(new->title, temp, OPTION_TITLE_LEN-1);
		new->title[OPTION_TITLE_LEN-1] = 0;

		// copy values (suboption names)
		dst = (char*)new + sizeof(option_t);
		for(j = 0; j < MAXOPTIONS; j++)
		{
			sprintf(tmpath, "value%i", j);
			temp = I_GetValue(tmpath);
			if(!temp)
				break;
			strcpy(dst, temp);
			dst += strlen(temp) + 1;
		}
		*dst = 0xFF; // terminator
		dst++;

		// copy 'parameter'
		temp = I_GetValue("parameter");
		if(temp)
		{
			strcpy(dst, temp);
			dst += strlen(temp);
		} else
			*dst = 0;
		dst++;

		// copy params (suboption parameters)
		for(j = 0; j < numval; j++)
		{
			sprintf(tmpath, "param%i", j);
			temp = I_GetValue(tmpath);
			if(temp)
			{
				strcpy(dst, temp);
				dst += strlen(temp);
			} else
				*dst = 0;
			dst++;
		}

		// link this option to chain
		*opt = new;
		opt = &new->next;
		cur++;
	}

	// app icon; must be last - overwites INI
	if(!I_GetSection("app", 0))
		return 0; // should not happen
	temp = I_GetValue("icon");
	if(temp)
	{
		if(strlen(temp) < 32)
		{
			// BMP icon
			sprintf(tmpath, "%s/%s", path, temp);

			i = S_ReadFile(tmpath, filetmp, sizeof(filetmp));
			if(i <= 0)
			{
				printf("- failed to read '%s' %i\n", tmpath, -i);
				temp = NULL; // force random icon
			} else
			if(GFX_IconFromBMP(filetmp, &apps[numapps].icon))
				// error, force random icon
				temp = NULL;
		}
	}

	if(!temp)
	{
		// random icon
		int j;
		color_t *pal = apps[numapps].icon.palette;
		uint8_t *dst = apps[numapps].icon.pixels;

		pal->channel.r = (numapps & 1) * 0x80;
		pal->channel.g = (numapps & 2) * 0x40;
		pal->channel.b = (numapps & 4) * 0x20;
		pal->channel.a = 0xFF;

		if(numapps & 8)
		{
			pal->channel.r += 0x60;
			pal->channel.g += 0x60;
			pal->channel.b += 0x60;
		}

		for(j = 1; j < 8; j++)
		{
			pal[j].channel.r = pal[0].channel.r + j*2;
			pal[j].channel.g = pal[0].channel.g + j*2;
			pal[j].channel.b = pal[0].channel.b + j*2;
			pal[j].channel.a = pal[0].channel.a;
		}

		for(j = 0; j < GFX_ICON_SIZE * GFX_ICON_SIZE; j++)
		{
			*dst = rand() & 7;
			dst++;
		}
	}

	numapps++;
	return numapps == MAXAPPS;
}

int A_Init()
{
	// clear options
	numapps = 0;
	S_FreeMemory();
	// load app list
#ifdef LINUX
	DIR *d;
	struct dirent *ent;

	d = opendir("./");
	if(d)
	{
		while((ent = readdir(d)) != NULL)
			if(ent->d_type == DT_DIR && ent->d_name[0] != '.' && A_AddNew(ent->d_name))
				break;
		closedir(d);
	}
#else
	char templist[1024];
	int size;
	char *src, *tmp;;

	size = S_ReadFile("app_list", templist, sizeof(templist)-1);

	if(size <= 0)
	{
		printf("A_Init: failed to get app list %i\n", size);
		return 0;
	}

	templist[size] = 0;
	src = templist;
	tmp = templist;
	while(1)
	{
		if(*src == '\n' || !*src)
		{
			char old = *src;

			*src = 0;
			if(A_AddNew(tmp))
				break;
			if(!old)
				break;
			src++;
			tmp = src;
		} else
			src++;
	}
#endif
	return numapps;
}

void A_Destroy()
{
	numapps = 0;
}

