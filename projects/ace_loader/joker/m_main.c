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

// selection
int soffset, maincount;
int mainsel;

static char msg_exit[] = "Press ➕ or ➖ to exit loader.";

// navigation

void ecb_main(int act)
{
	int tmpsel = mainsel;
	int fakecount;

	if(!maincount && act != AKEY_KO)
		return;

	if(maincount % GFX_LAYOUT_XCOUNT)
		fakecount = ((maincount + GFX_LAYOUT_XCOUNT) / GFX_LAYOUT_XCOUNT) * GFX_LAYOUT_XCOUNT;
	else
		fakecount = maincount;

	switch(act)
	{
		case AKEY_OPTIONS:
			if(mainsel >= maincount)
				break;
			// enter options menu
			redraw_options();
			return;
		break;
		case AKEY_UP:
			if(mainsel >= GFX_LAYOUT_XCOUNT)
				mainsel -= GFX_LAYOUT_XCOUNT;
		break;
		case AKEY_DOWN:
			mainsel += GFX_LAYOUT_XCOUNT;
			if(mainsel >= (fakecount))
				mainsel -= GFX_LAYOUT_XCOUNT;
		break;
		case AKEY_RIGHT:
			if((tmpsel % GFX_LAYOUT_XCOUNT) != (GFX_LAYOUT_XCOUNT-1) && mainsel < (fakecount-1))
				mainsel++;
		break;
		case AKEY_LEFT:
			if(tmpsel % GFX_LAYOUT_XCOUNT)
				mainsel--;
		break;
		case AKEY_OK:
			// run app
			start_app();
			return;
		break;
		case AKEY_KO:
			// just ask first
			draw_message(msg_exit, -1);
		break;
	}

	if(tmpsel != mainsel)
	{
		int tmpo = soffset;
		// check row
		if(mainsel < soffset)
			soffset = (mainsel / GFX_LAYOUT_XCOUNT) * GFX_LAYOUT_XCOUNT;
		if(mainsel >= soffset + GFX_LAYOUT_XCOUNT * GFX_LAYOUT_YCOUNT)
			soffset = ((mainsel - GFX_LAYOUT_XCOUNT) / GFX_LAYOUT_XCOUNT) * GFX_LAYOUT_XCOUNT;
		// check redraw
		if(tmpo != soffset)
			draw_slots();
		// offset mainsel
		tmpsel = mainsel - soffset;
		// remove old selection
		GFX_Selection(selx, sely, selw, selh, (color_t)GFX_COLOR_BACKGROUND);
		// update coords
		selx = GFX_LAYOUT_STARTX + (tmpsel % GFX_LAYOUT_XCOUNT) * GFX_LAYOUT_STEPX;
		sely = GFX_LAYOUT_STARTY + (tmpsel / GFX_LAYOUT_XCOUNT) * GFX_LAYOUT_STEPY;
		selx -= GFX_SEL_SPACE + GFX_SEL_EDGE;
		sely -= GFX_SEL_SPACE + GFX_SEL_EDGE;
	}
}

// drawing

void draw_slots()
{
	int x, y;
	int xp, yp;
	int idx = soffset;

	yp = GFX_LAYOUT_STARTY;

	for(y = 0; y < GFX_LAYOUT_YCOUNT; y++)
	{
		xp = GFX_LAYOUT_STARTX;
		for(x = 0; x < GFX_LAYOUT_XCOUNT; x++)
		{
			GFX_IconSlot(xp, yp);
			if(idx < maincount)
				GFX_RectPixels8Bit(xp, yp, GFX_ICON_SIZE, GFX_ICON_SIZE, &apps[idx].icon);
			xp += GFX_LAYOUT_STEPX;
			idx++;
		}
		yp += GFX_LAYOUT_STEPY;
	}
}

void redraw_main()
{
	int tmpsel = mainsel - soffset;

	key_cb = ecb_main;

	if(maincount)
	{
		// selection
		selx = GFX_LAYOUT_STARTX + (tmpsel % GFX_LAYOUT_XCOUNT) * GFX_LAYOUT_STEPX;
		sely = GFX_LAYOUT_STARTY + (tmpsel / GFX_LAYOUT_XCOUNT) * GFX_LAYOUT_STEPY;
		selx -= GFX_SEL_SPACE + GFX_SEL_EDGE;
		sely -= GFX_SEL_SPACE + GFX_SEL_EDGE;
		selw = GFX_ICON_SIZE + (GFX_SEL_SPACE + GFX_SEL_EDGE)*2;
		selh = selw;
	} else
		selw = 0;

	// background + stuff
	GFX_ClearColor((color_t)GFX_COLOR_BACKGROUND);
	GFX_RectClear(GFX_LAYOUT_LINEX, GFX_LAYOUT_LINEY, GFX_LAYOUT_LINEW, 1, (color_t)0xFFFFFFFF);

	// slots + selection
	draw_slots();

	// help
	kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR);
	kfn_write(GFX_MAIN_HELPX, GFX_MAIN_HELPY, "➕ / ➖ Options   Ⓑ Back   Ⓐ Start");
}

