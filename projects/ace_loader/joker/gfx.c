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

#define BMP_SIG	0x4D42

typedef struct
{
	uint16_t signature; // BMP_SIG
	uint32_t filesize;
	uint16_t reserved[2]; // 0
	uint32_t imgstart;
	uint32_t headsize;
	uint32_t width;
	uint32_t height;
	uint16_t planes; // 1
	uint16_t bpp; // 1, 4, 8, 24, 32
	uint32_t compres; // 0
	uint32_t imgsize;
	uint32_t etc[4];
} __attribute__((packed)) bmphead_t;

typedef struct
{
	uint8_t b, g, r, a;
} __attribute__((packed)) bmppal_t;

//
// simple

void GFX_HideScreen(int hide)
{
	int i = SCREENWIDTH * SCREENHEIGHT;
	color_t *dst = framebuffer;

	if(hide)
		hide = 0;
	else
		hide = 0xFF;

	while(i--)
	{
		dst->channel.a = hide;
		dst++;
	}
}

void GFX_ClearColor(color_t col)
{
	int i = SCREENWIDTH * SCREENHEIGHT;
	color_t *dst = framebuffer;

	while(i--)
	{
		*dst = col;
		dst++;
	}
}

void GFX_RectClear(int x, int y, int w, int h, color_t col)
{
	color_t *dst = framebuffer + x + y * SCREENWIDTH;

	for(y = 0; y < h; y++)
	{
		for(x = 0; x < w; x++)
		{
			*dst = col;
			dst++;
		}
		dst += SCREENWIDTH - w;
	}
}

void GFX_RectHGradient(int x, int y, int w, int h, color_t col, uint8_t start, int16_t step)
{
	int16_t alpha = start * 256;
	color_t *dst = framebuffer + x + y * SCREENWIDTH;

	for(y = 0; y < h; y++)
	{
		for(x = 0; x < w; x++)
		{
			GFX_Blend(dst->channel.r, col.channel.r, alpha / 256);
			GFX_Blend(dst->channel.g, col.channel.g, alpha / 256);
			GFX_Blend(dst->channel.b, col.channel.b, alpha / 256);
			dst++;
		}
		dst += SCREENWIDTH - w;
		alpha += step;
	}
}

void GFX_RectVGradient(int x, int y, int w, int h, color_t col, uint8_t start, int16_t step)
{
	int16_t alpha;
	int16_t oal = start * 256;
	color_t *dst = framebuffer + x + y * SCREENWIDTH;

	for(y = 0; y < h; y++)
	{
		alpha = oal;
		for(x = 0; x < w; x++)
		{
			GFX_Blend(dst->channel.r, col.channel.r, alpha / 256);
			GFX_Blend(dst->channel.g, col.channel.g, alpha / 256);
			GFX_Blend(dst->channel.b, col.channel.b, alpha / 256);
			dst++;
			alpha += step;
		}
		dst += SCREENWIDTH - w;
	}
}

void GFX_RectPixels8Bit(int x, int y, int w, int h, icon8bit_t *icon)
{
	uint8_t *src = icon->pixels;
	color_t *pal = icon->palette;
	color_t *dst = framebuffer + x + y * SCREENWIDTH;

	for(y = 0; y < h; y++)
	{
		for(x = 0; x < w; x++)
		{
			*dst = pal[*src];
			src++;
			dst++;
		}
		dst += SCREENWIDTH - w;
	}
}

//
// combined

void GFX_IconSlot(int x, int y)
{
	// top
	GFX_RectClear(x, y, GFX_ICON_SIZE, GFX_ICON_EDGE, (color_t)GFX_COLOR_SLOTEDGE); // edge
	GFX_RectHGradient(x + 1, y - 3, GFX_ICON_SIZE - 2, 3, (color_t)GFX_COLOR_SHADOW, 10, 15 * 256); // gradient
	// bottom
	GFX_RectClear(x, y + GFX_ICON_SIZE - GFX_ICON_EDGE, GFX_ICON_SIZE, GFX_ICON_EDGE, (color_t)GFX_COLOR_SLOTEDGE); // edge
	GFX_RectHGradient(x + 1, y + GFX_ICON_SIZE, GFX_ICON_SIZE - 2, 3, (color_t)GFX_COLOR_SHADOW, 40, -15 * 256); // gradient
	// left
	GFX_RectClear(x, y + GFX_ICON_EDGE, GFX_ICON_EDGE, GFX_ICON_SIZE - GFX_ICON_EDGE*2, (color_t)GFX_COLOR_SLOTEDGE); // edge
	GFX_RectVGradient(x - 3, y + 1, 3, GFX_ICON_SIZE - 2, (color_t)GFX_COLOR_SHADOW, 10, 15 * 256); // gradient
	// right
	GFX_RectClear(x + GFX_ICON_SIZE - GFX_ICON_EDGE, y + GFX_ICON_EDGE, GFX_ICON_EDGE, GFX_ICON_SIZE - GFX_ICON_EDGE*2, (color_t)GFX_COLOR_SLOTEDGE); // edge
	GFX_RectVGradient(x + GFX_ICON_SIZE, y + 1, 3, GFX_ICON_SIZE - 2, (color_t)GFX_COLOR_SHADOW, 40, -15 * 256); // gradient
	// inside
	GFX_RectClear(x + GFX_ICON_EDGE, y + GFX_ICON_EDGE, GFX_ICON_SIZE - GFX_ICON_EDGE*2, GFX_ICON_SIZE - GFX_ICON_EDGE*2, (color_t)GFX_COLOR_SLOTBACK);
}

void GFX_Selection(int x, int y, int w, int h, color_t col)
{
	// top
	GFX_RectClear(1 + x, y, w-2, GFX_SEL_EDGE, col);
	// left
	GFX_RectClear(x, 1 + y, GFX_SEL_EDGE, h-2, col);
	// bottom
	GFX_RectClear(1 + x, (y + h) - GFX_SEL_EDGE, w-2, GFX_SEL_EDGE, col);
	// right
	GFX_RectClear((x + w) - GFX_SEL_EDGE, 1 + y, GFX_SEL_EDGE, h-2, col);
}

int GFX_IconFromBMP(void *buff, icon8bit_t *icon)
{
	int i, j;
	bmppal_t *psrc;
	color_t *pdst;
	uint8_t *pixels, *dst;
	bmphead_t *head = buff;

	if(head->signature != BMP_SIG || head->headsize > 1024 || head->planes != 1 || head->compres || head->imgstart > 2048)
	{
		printf("- invalid bitmap\n");
		return 1;
	}

	if(head->width != GFX_ICON_SIZE || head->height != GFX_ICON_SIZE || head->bpp != 8)
	{
		printf("- only %ix%ix8 bitmap is supported\n", GFX_ICON_SIZE, GFX_ICON_SIZE);
		return 1;
	}

	// palette
	psrc = buff + head->headsize + 14;
	pdst = icon->palette;
	for(i = 0; i < 256; i++)
	{
		pdst->channel.r = psrc->r;
		pdst->channel.g = psrc->g;
		pdst->channel.b = psrc->b;
		pdst->channel.a = 0xFF;
		pdst++;
		psrc++;
	}

	pixels = buff + head->imgstart + (GFX_ICON_SIZE * GFX_ICON_SIZE) + GFX_ICON_SIZE;
	dst = icon->pixels;
	for(i = 0; i < GFX_ICON_SIZE; i++)
	{
		pixels -= GFX_ICON_SIZE * 2;
		for(j = 0; j < GFX_ICON_SIZE; j++)
		{
			*dst = *pixels;
			dst++;
			pixels++;
		}
	}

	return 0;
}

void GFX_MiniPixels8Bit(int x, int y, int w, int h, icon8bit_t *icon, int nw, int nh)
{
	int stepx, stepy;
	uint8_t *src = icon->pixels;
	color_t *pal = icon->palette;
	color_t *dst = framebuffer + x + y * SCREENWIDTH;

	stepy = 0;
	for(y = 0; y < h; y++)
	{
		color_t *tmp = dst;
		uint8_t *t2 = src;
		stepx = 0;
		for(x = 0; x < w; x++)
		{
			uint16_t r, g, b, c;
			color_t tcol = pal[*src];
			if(stepy < nh) // might not be correct
			{
				r = tcol.channel.r;
				g = tcol.channel.g;
				b = tcol.channel.b;
				c = 1;
			} else
			{
				r = tcol.channel.r + dst->channel.r;
				g = tcol.channel.g + dst->channel.g;
				b = tcol.channel.b + dst->channel.b;
				c = 2;
			}
			src++;
			while(x < w)
			{
				stepx += nw;
				if(stepx >= w)
					break;
				color_t tcol = pal[*src];
				r += tcol.channel.r;
				g += tcol.channel.g;
				b += tcol.channel.b;
				c++;
				src++;
				x++;
			}
			dst->channel.r = r / c;
			dst->channel.g = g / c;
			dst->channel.b = b / c;
			dst->channel.a = tcol.channel.a;
			dst++;
			stepx -= w;
		}
		stepy += nh;
		if(stepy >= h)
		{
			stepy -= h;
			dst = tmp + SCREENWIDTH;
		} else
			dst = tmp;
		src = t2 + w;
	}
}

