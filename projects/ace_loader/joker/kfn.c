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

#include "fonts.h"

#define KFN_ID	0x006e666b

// kfn info
typedef struct
{
	uint32_t id;
	uint8_t format;
	uint8_t reserved;
	uint16_t line_height;
	uint16_t num_ranges;
} __attribute__((packed)) kfn_head_t;

// character info
typedef struct
{
	uint16_t w, h;
	int16_t x, y, s;
	uint32_t pixo;
} __attribute__((packed)) kfn_cinfo_t;

// ranges
typedef struct
{
	uint16_t first;
	uint16_t count;
} kfn_range_t;

// font list
static const kfn_head_t *kfn_list[] =
{
	(const kfn_head_t *)font_big,
	(const kfn_head_t *)font_medium,
	(const kfn_head_t *)font_small
};

// selected font
static const kfn_head_t *kfn_cur;
color_t kfn_color = (color_t)0xFFFFFFFF;

void kfn_setfont(int font, color_t color)
{
	kfn_cur = kfn_list[font];
	kfn_color = color;
}

int kfn_height()
{
	return kfn_cur->line_height;
}

void kfn_drawchar(int x, int y, const kfn_cinfo_t *info)
{
	int px, py;
	color_t *dst;
	const uint8_t *src;

	x += info->x;
	y += info->y;

	dst = framebuffer + x + y * SCREENWIDTH;
//	src = (const uint8_t*)kfn_cur + info->pixo;
	memcpy(&py, &info->pixo, sizeof(uint32_t));
	src = (const uint8_t*)kfn_cur + py;

	for(py = 0; py < info->h; py++)
	{
		for(px = 0; px < info->w; px++)
		{
			if(*src == 0xFF)
			{
				dst->channel.r = kfn_color.channel.r;
				dst->channel.g = kfn_color.channel.g;
				dst->channel.b = kfn_color.channel.b;
			} else
			if(*src)
			{
				GFX_Blend(dst->channel.r, kfn_color.channel.r, *src);
				GFX_Blend(dst->channel.g, kfn_color.channel.g, *src);
				GFX_Blend(dst->channel.b, kfn_color.channel.b, *src);
			}
			src++;
			dst++;
		}
		dst += SCREENWIDTH - info->w;
	}
}

int kfn_putchar(int x, int y, uint16_t in)
{
	int i, r;
	const void *kfn = kfn_cur + 1; // skip header

	r = kfn_cur->num_ranges;
	for(i = 0; i < r; i++)
	{
		// check for character in this range
		if(in >= ((kfn_range_t*)kfn)->first && in < ((kfn_range_t*)kfn)->first + ((kfn_range_t*)kfn)->count)
		{
			// found
			const kfn_cinfo_t *info;

			in -= ((kfn_range_t*)kfn)->first;
			info = kfn + sizeof(kfn_range_t) + in * sizeof(kfn_cinfo_t);

			kfn_drawchar(x, y, info);
			return info->s;
		}
		// skip this range
		kfn += sizeof(kfn_range_t) + ((kfn_range_t*)kfn)->count * sizeof(kfn_cinfo_t);
	}
	return 0;
}

void kfn_write(int x, int y, const char *text)
{
	uint16_t out;
	int ust = 0;

	while(*text)
	{
		// UTF-8
		if(*text & 0x80)
		{
			if((*text & 0b11100000) == 0b11000000)
			{
				ust = 1;
				out = *text & 0b00011111;
			} else
			if((*text & 0b11110000) == 0b11100000)
			{
				ust = 2;
				out = *text & 0b00001111;
			} else
			if(ust)
			{
				ust--;
				out <<= 6;
				out |= *text & 0b00111111;
				if(!ust)
				{
					// show
					x += kfn_putchar(x, y, out);
				}
			}
			text++;
			continue;
		} else
		{
			out = *text;
			ust = 0;
		}
		// show
		x += kfn_putchar(x, y, out);
		text++;
	}
}

int kfn_addchar(uint16_t in)
{
	int i, r;
	const void *kfn = kfn_cur + 1; // skip header

	r = kfn_cur->num_ranges;
	for(i = 0; i < r; i++)
	{
		// check for character in this range
		if(in >= ((kfn_range_t*)kfn)->first && in < ((kfn_range_t*)kfn)->first + ((kfn_range_t*)kfn)->count)
		{
			// found
			const kfn_cinfo_t *info;

			in -= ((kfn_range_t*)kfn)->first;
			info = kfn + sizeof(kfn_range_t) + in * sizeof(kfn_cinfo_t);

			return info->s;
		}
		// skip this range
		kfn += sizeof(kfn_range_t) + ((kfn_range_t*)kfn)->count * sizeof(kfn_cinfo_t);
	}
	return 0;
}

int kfn_textwidth(const char *text)
{
	uint16_t out;
	int x = 0;
	int ust = 0;

	while(*text)
	{
		// UTF-8
		if(*text & 0x80)
		{
			if((*text & 0b11100000) == 0b11000000)
			{
				ust = 1;
				out = *text & 0b00011111;
			} else
			if((*text & 0b11110000) == 0b11100000)
			{
				ust = 2;
				out = *text & 0b00001111;
			} else
			if(ust)
			{
				ust--;
				out <<= 6;
				out |= *text & 0b00111111;
				if(!ust)
				{
					// add
					x += kfn_addchar(out);
				}
			}
			text++;
			continue;
		} else
		{
			out = *text;
			ust = 0;
		}
		// add
		x += kfn_addchar(out);
		text++;
	}
	return x;
}

