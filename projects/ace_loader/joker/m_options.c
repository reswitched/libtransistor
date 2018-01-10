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
static int optsel;
static int optmax;
option_t *optcur;

// suboptions
static int submax;
static char *subtext;

// navigation

void ecb_options(int act)
{
	int tmpsel = optsel;

	if(!optmax && act != AKEY_KO)
		return;

	switch(act)
	{
		case AKEY_OK:
		case AKEY_RIGHT:
			// move selection
			selx = GFX_SOPT_OPTX - GFX_OPT_OPTS;
			sely = GFX_SOPT_OPTY - GFX_OPT_OPTS + optcur->choice * GFX_OPT_OPTH;
			selw = GFX_SOPT_SELW;
			selh = GFX_SOPT_OPTH + GFX_OPT_OPTS;
			// enter suboptions
			key_cb = ecb_subopt;
			// draw selection
			ecb_subopt(AKEY_DRAWSEL);
		break;
		case AKEY_KO:
			// enter main menu
			redraw_main();
			return;
		break;
		case AKEY_UP:
			if(optsel)
				optsel--;
		break;
		case AKEY_DOWN:
			if(optsel < optmax - 1)
				optsel++;
		break;
		case AKEY_DRAWSEL:
			// force update
			tmpsel = -1;
		break;
	}

	if(tmpsel != optsel || key_cb != ecb_options)
	{
		if(tmpsel >= 0)
		{
			// clear previous
			if(key_cb == ecb_options)
			{
				// normal clear
				GFX_RectClear(GFX_OPT_OPTSX - GFX_OPT_OPTS, GFX_OPT_OPTY - GFX_OPT_OPTS + tmpsel * GFX_OPT_OPTH, GFX_OPT_OPTSW, GFX_OPT_OPTH + GFX_OPT_OPTS, (color_t)GFX_COLOR_OPT_BGRAD);
				kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR);
				kfn_write(GFX_OPT_OPTX, GFX_OPT_OPTY + tmpsel * GFX_OPT_OPTH, optcur->title);
			} else
			{
				// special clear
				GFX_RectClear(GFX_OPT_OPTSX - GFX_OPT_OPTS, GFX_OPT_OPTY - GFX_OPT_OPTS + tmpsel * GFX_OPT_OPTH, GFX_OPT_OPTSW, GFX_OPT_OPTH + GFX_OPT_OPTS, (color_t)GFX_COLOR_OPT_BGRAD);
				GFX_RectClear(GFX_OPT_OPTSX - GFX_OPT_OPTS + GFX_SEL_EDGE + 2 * GFX_SEL_EDGE, GFX_OPT_OPTY + tmpsel * GFX_OPT_OPTH - GFX_OPT_OPTS + GFX_SEL_EDGE + 2 * GFX_SEL_EDGE, GFX_SEL_EDGE, GFX_OPT_OPTH - 3 * GFX_SEL_EDGE, (color_t)GFX_TEXT_COLOR_SEL);
				kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR_SEL);
				kfn_write(GFX_OPT_OPTX, GFX_OPT_OPTY + tmpsel * GFX_OPT_OPTH, optcur->title);
			}
		}
		if(key_cb == ecb_options)
		{
			// update option
			tmpsel = optsel;
			optcur = apps[mainsel].options;
			while(tmpsel--)
				optcur = optcur->next;
			// draw new one
			tmpsel = GFX_OPT_OPTY + optsel * GFX_OPT_OPTH;
			GFX_RectClear(GFX_OPT_OPTSX - GFX_OPT_OPTS + GFX_SEL_EDGE, tmpsel - GFX_OPT_OPTS + GFX_SEL_EDGE, GFX_OPT_OPTSW - 2 * GFX_SEL_EDGE, GFX_OPT_OPTH + GFX_OPT_OPTS - 2 * GFX_SEL_EDGE, (color_t)GFX_COLOR_OPT_SEL);
			GFX_RectClear(GFX_OPT_OPTSX - GFX_OPT_OPTS + GFX_SEL_EDGE + 2 * GFX_SEL_EDGE, tmpsel - GFX_OPT_OPTS + GFX_SEL_EDGE + 2 * GFX_SEL_EDGE, GFX_SEL_EDGE, GFX_OPT_OPTH - 3 * GFX_SEL_EDGE, (color_t)GFX_TEXT_COLOR_SEL);
			kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR_SEL);
			kfn_write(GFX_OPT_OPTX, tmpsel, optcur->title);
			// update coords
			sely = GFX_OPT_OPTY - GFX_OPT_OPTS + optsel * GFX_OPT_OPTH;
			// update suboptions
			draw_suboptions();
		}
	}
}

void ecb_subopt(int act)
{
	int tmpsel = optcur->choice;

	switch(act)
	{
		case AKEY_KO:
		case AKEY_LEFT:
			// set selection
			selx = GFX_OPT_OPTSX - GFX_OPT_OPTS;
			sely = GFX_OPT_OPTY - GFX_OPT_OPTS + optsel * GFX_OPT_OPTH;
			selw = GFX_OPT_OPTSW;
			selh = GFX_OPT_OPTH + GFX_OPT_OPTS;
			// enter options
			key_cb = ecb_options;
			// draw selection
			ecb_options(AKEY_DRAWSEL);
		break;
		case AKEY_UP:
			if(optcur->choice)
				optcur->choice--;
		break;
		case AKEY_DOWN:
			if(optcur->choice < submax - 1)
				optcur->choice++;
		break;
		case AKEY_OK:
			// pick option
			switch(optcur->type)
			{
				case OPTYPE_ENUM0:
					optcur->value = (1 << optcur->choice);
					// redraw all
					draw_suboptions();
					tmpsel = -1;
				break;
				case OPTYPE_ENUM1:
					if(optcur->value & (1 << optcur->choice))
						optcur->value = 0;
					else
						optcur->value = (1 << optcur->choice);
					// redraw all
					draw_suboptions();
					tmpsel = -1;
				break;
				case OPTYPE_BOOLEAN:
					optcur->value ^= (1 << optcur->choice);
					// force update
					tmpsel = -1;
				break;
			}
		break;
		case AKEY_DRAWSEL:
			// force update
			tmpsel = -1;
		break;
	}

	if(tmpsel != optcur->choice || key_cb != ecb_subopt)
	{
		int i;

		if(tmpsel >= 0)
		{
			// clear previous
			GFX_RectClear(GFX_SOPT_OPTX - GFX_OPT_OPTS, GFX_SOPT_OPTY - GFX_OPT_OPTS + tmpsel * GFX_OPT_OPTH, GFX_SOPT_SELW, GFX_SOPT_OPTH + GFX_OPT_OPTS, (color_t)GFX_COLOR_OPT_BG);
			if((1 << tmpsel) & optcur->value)
				kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR_SEL);
			else
				kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR);
			kfn_write(GFX_SOPT_OPTX, GFX_SOPT_OPTY + GFX_SOPT_OPTH * tmpsel, subtext);
			// update text
			subtext = (char*)optcur + sizeof(option_t);
			for(i = 0; 1; i++)
			{
				if(i == optcur->choice)
					break;
				subtext += strlen(subtext) + 1;
			}
		}
		if(key_cb == ecb_subopt)
		{
			// update coords
			tmpsel = GFX_SOPT_OPTY + GFX_SOPT_OPTH * optcur->choice;
			sely = tmpsel - GFX_OPT_OPTS;
			// draw new selection
			GFX_RectClear(GFX_SOPT_OPTX - GFX_OPT_OPTS + GFX_SEL_EDGE, tmpsel - GFX_OPT_OPTS + GFX_SEL_EDGE, GFX_SOPT_SELW - 2 * GFX_SEL_EDGE, GFX_SOPT_OPTH + GFX_OPT_OPTS - 2 * GFX_SEL_EDGE, (color_t)GFX_COLOR_OPT_SEL);
			if((1 << optcur->choice) & optcur->value)
				kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR_SEL);
			else
				kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR);
			kfn_write(GFX_SOPT_OPTX, tmpsel, subtext);
		}
	}
}

// drawing

void redraw_options()
{
	int i, y;
	option_t *opt;

	selw = 0;

	optmax = 0;
	optsel = 0;
	key_cb = ecb_options;

	// main frame
	GFX_RectClear(0, 0, GFX_OPT_STARTX, SCREENHEIGHT, (color_t)GFX_COLOR_OPT_BACK);
	GFX_RectClear(GFX_OPT_STARTX, 0, GFX_OPT_WIDTH, SCREENHEIGHT, (color_t)GFX_COLOR_OPT_BG);
	GFX_RectClear(GFX_OPT_STARTX + GFX_OPT_WIDTH, 0, SCREENWIDTH - (GFX_OPT_STARTX + GFX_OPT_WIDTH), SCREENHEIGHT, (color_t)GFX_COLOR_OPT_BACK);
	// lines
	GFX_RectClear(GFX_OPT_LINEX, GFX_OPT_LIN1Y, GFX_OPT_LINEW, 1, (color_t)GFX_COLOR_LINE);
	GFX_RectClear(GFX_OPT_LINEX, GFX_OPT_LIN2Y, GFX_OPT_LINEW, 1, (color_t)GFX_COLOR_LINE);

	// miniature
	GFX_RectHGradient(GFX_OPT_ICONX + 1, GFX_OPT_ICONY - 3, GFX_OPT_ICONS - 2, 3, (color_t)GFX_COLOR_SHADOW, 15, 15 * 256); // gradient top
	GFX_RectHGradient(GFX_OPT_ICONX + 1, GFX_OPT_ICONY + GFX_OPT_ICONS, GFX_OPT_ICONS - 2, 3, (color_t)GFX_COLOR_SHADOW, 45, -15 * 256); // gradient bottom
	GFX_RectVGradient(GFX_OPT_ICONX - 3, GFX_OPT_ICONY + 1, 3, GFX_OPT_ICONS - 2, (color_t)GFX_COLOR_SHADOW, 15, 15 * 256); // gradient left
	GFX_RectVGradient(GFX_OPT_ICONX + GFX_OPT_ICONS, GFX_OPT_ICONY + 1, 3, GFX_OPT_ICONS - 2, (color_t)GFX_COLOR_SHADOW, 45, -15 * 256); // gradient
	GFX_MiniPixels8Bit(GFX_OPT_ICONX, GFX_OPT_ICONY, GFX_ICON_SIZE, GFX_ICON_SIZE, &apps[mainsel].icon, GFX_OPT_ICONS, GFX_OPT_ICONS);

	// title
	kfn_setfont(FONT_BIG, (color_t)GFX_TEXT_COLOR);
	kfn_write(GFX_OPT_TITLEX, GFX_OPT_TITLEY, apps[mainsel].name);
	// version + author
	kfn_setfont(FONT_SMALL, (color_t)GFX_TEXT_COLOR);
	kfn_write(GFX_OPT_TITLEX, GFX_OPT_INFOY, apps[mainsel].info);

	// options
	if(apps[mainsel].options)
	{
		// gradient
		GFX_RectHGradient(GFX_OPT_STARTX, GFX_OPT_GRADY, GFX_OPT_GRADW, GFX_OPT_GRADHG, (color_t)0xFFFFFFFF, 1, 32);
		GFX_RectClear(GFX_OPT_STARTX, GFX_OPT_GRADY + GFX_OPT_GRADHG, GFX_OPT_GRADW, GFX_OPT_GRADH - GFX_OPT_GRADHG*2, (color_t)GFX_COLOR_OPT_BGRAD);
		GFX_RectHGradient(GFX_OPT_STARTX, GFX_OPT_GRADY + (GFX_OPT_GRADH - GFX_OPT_GRADHG), GFX_OPT_GRADW, GFX_OPT_GRADHG, (color_t)0xFFFFFFFF, 8, -32);
		// help
		kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR);
		kfn_write(GFX_OPT_HELPX, GFX_OPT_HELPY, "Ⓑ Back       Ⓐ OK");
		// draw options
		opt = apps[mainsel].options;
		selx = GFX_OPT_OPTSX - GFX_OPT_OPTS;
		sely = GFX_OPT_OPTY - GFX_OPT_OPTS + optsel * GFX_OPT_OPTH;
		selw = GFX_OPT_OPTSW;
		selh = GFX_OPT_OPTH + GFX_OPT_OPTS;
		y = GFX_OPT_OPTY;
		for(i = 0; opt; i++)
		{
			if(optsel == i)
			{
				optcur = opt;
				GFX_RectClear(GFX_OPT_OPTSX - GFX_OPT_OPTS + GFX_SEL_EDGE, y - GFX_OPT_OPTS + GFX_SEL_EDGE, GFX_OPT_OPTSW - 2 * GFX_SEL_EDGE, GFX_OPT_OPTH + GFX_OPT_OPTS - 2 * GFX_SEL_EDGE, (color_t)GFX_COLOR_OPT_SEL);
				GFX_RectClear(GFX_OPT_OPTSX - GFX_OPT_OPTS + GFX_SEL_EDGE + 2 * GFX_SEL_EDGE, y - GFX_OPT_OPTS + GFX_SEL_EDGE + 2 * GFX_SEL_EDGE, GFX_SEL_EDGE, GFX_OPT_OPTH - 3 * GFX_SEL_EDGE, (color_t)GFX_TEXT_COLOR_SEL);
				kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR_SEL);
			} else
				kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR);

			kfn_write(GFX_OPT_OPTX, y, opt->title);
			y += GFX_OPT_OPTH;

			opt = opt->next;
		}
		optmax = i;
		draw_suboptions();
	} else
	{
		kfn_setfont(FONT_SMALL, (color_t)GFX_TEXT_COLOR);
		kfn_write(GFX_OPT_NOPTX, GFX_OPT_NOPTY, "This app has no options.");
		// help
		kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR);
		kfn_write(GFX_OPT_HELPX + 120, GFX_OPT_HELPY, "Ⓑ Back");
	}
}

void draw_suboptions()
{
	int i, y;
	char *src = (char*)optcur + sizeof(option_t);

	// clear
	GFX_RectClear(GFX_SOPT_BACKX, GFX_SOPT_BACKY, GFX_SOPT_BACKW, GFX_SOPT_BACKH, (color_t)GFX_COLOR_OPT_BG);

	y = GFX_SOPT_OPTY;
	for(i = 0; 1; i++)
	{
		if(*src == (char)0xFF)
			// terminator hit
			break;
		// title
		if(i == optcur->choice)
			subtext = src;
		if((1 << i) & optcur->value)
			kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR_SEL);
		else
			kfn_setfont(FONT_MEDIUM, (color_t)GFX_TEXT_COLOR);
		kfn_write(GFX_SOPT_OPTX, y, src);
		y += GFX_SOPT_OPTH;
		src += strlen(src) + 1;
	}
	submax = i;
}

