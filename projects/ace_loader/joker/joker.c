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
#include "system.h"
#include "gfx.h"
#include "apps.h"
#include "kfn.h"
#include "menu.h"

#ifndef LINUX
#include "../nro.h"
#include "../http.h"
#include "../memory.h"
#endif

// menu
void (*key_cb)(int);

// selection box
int selx, sely, selw, selh;
static color_t selc = (color_t)GFX_COLOR_SLOTSEL;

// exit message
int msg_special;

#ifndef LINUX
static char msg_start[] = "Starting app ...";
#endif

#ifdef LINUX
void nro_arg_name(char *text)
{
	printf("start: %s ", text);
}

void nro_add_arg(char *text)
{
	printf("%s ", text);
}
#endif

void start_app()
{
	int i, count;
	option_t *opt;

	if(mainsel >= maincount)
		return;

	// 'unselect'
	GFX_Selection(selx, sely, selw, selh, (color_t)GFX_COLOR_BACKGROUND);

	opt = apps[mainsel].options;

	// build command line for this app
	nro_arg_name(apps[mainsel].path);

	// go trough all options
	count = 0;
	while(opt)
	{
		char *src = (char*)opt + sizeof(option_t);

		// skip names, count suboptions
		while(*src != (char)0xFF)
		{
			if(!*src)
				count++;
			src++;
		}
		src++;

		// add 'parameter', if any
		if(*src)
		{
			if(opt->value)
				// only if at least one suboption is enabled
				nro_add_arg(src);
			while(*src)
				src++;
		}
		src++;

		// go trough all suboptions
		for(i = 0; i < count; i++)
		{
			if(opt->value & (1 << i) && *src)
				nro_add_arg(src);
			// next
			while(*src)
				src++;
			src++;
		}

		opt = opt->next;
	}

	// start this app
#ifdef LINUX
	printf("\n");
#else
	// message; downloading might take some time
	// this message will stay up until app starts using screen
	draw_message(msg_start, 1);
	S_UpdateScreen();

	// get NRO
	count = http_get_file(apps[mainsel].path, heap_base, heap_size);
	if(count > 0)
	{
		result_t r;

		// info
		printf("- starting %s\n", apps[mainsel].name);

		// load NRO
		r = nro_load(heap_base, count);
		if(r)
		{
			// load failed
			sprintf(filetmp, "Failed to load NRO.\nerror 0x%04X", r);
			draw_message(filetmp, 1);
		} else
		{
			// deinit HID; it's not shared
			hid_finalize();

			// start NRO
			r = nro_start();
			if(r)
			{
				// show return code
				sprintf(filetmp, "Non-zero return from NRO.\ncode 0x%08X", r);
				draw_message(filetmp, 1);
			}
			printf("- NRO returned 0x%08X\n", r);

			r = nro_unload();
			if(r)
			{
				// show unload error
				sprintf(filetmp, "NRO Unload failed.\nerror 0x%04X", r);
				draw_message(filetmp, 1);
			}

			// init HID again
			if(S_InitHid())
			{
				sprintf(filetmp, "HID init failed.\nCan't continue using GUI.\n\nExitting.");
				draw_message(filetmp, 0);
				stopped = 1;
			}
		}
	} else
	{
		// download failed
		sprintf(filetmp, "NRO Download failed.\nerror %i", -count);
		draw_message(filetmp, 1);
	}
#endif
}

void ecb_message(int act)
{
	switch(act)
	{
		case AKEY_OPTIONS:
			if(msg_special < 0)
				stopped = 1;
		break;
		case AKEY_KO:
		case AKEY_OK:
			// enter main menu
			redraw_main();
		break;
	}
}

void draw_message(char *msg, int special)
{
	int x, y;
	int cx = GFX_MESSAGE_CONTX;
	char *src = msg;

	GFX_RectClear(GFX_MESSAGE_BOXX, GFX_MESSAGE_BOXY, GFX_MESSAGE_BOXW, GFX_MESSAGE_BOXH, (color_t)GFX_MESSAGE_BACK);

	msg_special = special;
	if(special > 0)
	{
		// show icon
		GFX_RectHGradient(GFX_MESSAGE_ICONX + 1, GFX_MESSAGE_ICONY - 3, GFX_MESSAGE_ICONSIZE - 2, 3, (color_t)GFX_COLOR_SHADOW, 15, 15 * 256); // gradient top
		GFX_RectHGradient(GFX_MESSAGE_ICONX + 1, GFX_MESSAGE_ICONY + GFX_MESSAGE_ICONSIZE, GFX_MESSAGE_ICONSIZE - 2, 3, (color_t)GFX_COLOR_SHADOW, 45, -15 * 256); // gradient bottom
		GFX_RectVGradient(GFX_MESSAGE_ICONX - 3, GFX_MESSAGE_ICONY + 1, 3, GFX_MESSAGE_ICONSIZE - 2, (color_t)GFX_COLOR_SHADOW, 15, 15 * 256); // gradient left
		GFX_RectVGradient(GFX_MESSAGE_ICONX + GFX_MESSAGE_ICONSIZE, GFX_MESSAGE_ICONY + 1, 3, GFX_MESSAGE_ICONSIZE - 2, (color_t)GFX_COLOR_SHADOW, 45, -15 * 256); // gradient
		GFX_MiniPixels8Bit(GFX_MESSAGE_ICONX, GFX_MESSAGE_ICONY, GFX_ICON_SIZE, GFX_ICON_SIZE, &apps[mainsel].icon, GFX_MESSAGE_ICONSIZE, GFX_MESSAGE_ICONSIZE);
		// ofset text center
		cx = GFX_MESSAGE_CONTX2;
	}

	// count lines in message
	y = 1;
	while(*src)
	{
		if(*src == '\n')
			y++;
		src++;
	}

	// message text
	y = GFX_MESSAGE_BOXY + ((GFX_MESSAGE_SELY - GFX_MESSAGE_BOXY) / 2) - (kfn_height()/2) * y;
	src = msg;
	kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR);
	while(1)
	{
		if(*src == '\n' || !*src)
		{
			char tmp = *src;
			*src = 0;
			x = kfn_textwidth(msg) / 2;
			kfn_write(cx - x, y, msg);
			if(!tmp)
				break;
			*src = tmp;
			src++;
			msg = src;
			y += kfn_height();
		} else
			src++;
	}

	// handler
	key_cb = ecb_message;

	// button text
	x = kfn_textwidth("Close") / 2;
	kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR_SEL);
	kfn_write(GFX_MESSAGE_CONTX - x, GFX_MESSAGE_CONTY, "Close");

	// selection
	selx = GFX_MESSAGE_BOXX - 4;
	sely = GFX_MESSAGE_SELY - 4;
	selw = GFX_MESSAGE_BOXW + 8;
	selh = ((GFX_MESSAGE_BOXH + GFX_MESSAGE_BOXY) - GFX_MESSAGE_SELY) + 8;
}

static void color_animate()
{
	static int pos;
	static int step = 1;

	pos += step;
	if(pos == 128)
		step = -1;
	if(!pos)
		step = 1;

	if(pos & 3)
		return;

	if(step > 0)
	{
		selc.channel.r++;
		selc.channel.g++;
		selc.channel.b += 2;
	} else
	{
		selc.channel.r--;
		selc.channel.g--;
		selc.channel.b -= 2;
	}
}

#ifdef LINUX
int main(int argc, char **argv)
#else
int joker_main()
#endif
{
	int ret = S_Init();
	if(ret)
		return ret;

	// show main menu
	redraw_main();

	// update now
	S_UpdateScreen();

	// get all apps
	maincount = A_Init();

	// now draw icons
	redraw_main();
	draw_slots();

	while(!stopped)
	{
		S_HandleEvents(key_cb);
		color_animate();
		if(selw > 0)
			GFX_Selection(selx, sely, selw, selh, selc);
		S_UpdateScreen();
	}

	S_Deinit();

	return 0;
}

