#ifdef LINUX
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>
#else
#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#endif

#include "defs.h"
#include "system.h"

#ifndef LINUX
#include "../http.h"
#endif

int stopped;

#ifdef LINUX
color_t *framebuffer;
static SDL_Surface *screen;
// options memory
static void *optmem;
static int omax;
static int ocur;
#else
// local framebuffer
color_t framebuffer[1280 * 768];
// video
surface_t vidsurf;
revent_h vsync;
uint16_t swizzle[128*128];
// options memory
static uint8_t optmem[0x1000];
static int ocur;
// controls
#define SWBTN(x)	(1 << (x))
static hid_shared_memory_t *hmem;
static hid_controller_state_t *cst;
static uint64_t last_stamp;
static uint64_t buttons;
#endif

#ifndef LINUX

// controllers
int check_presence(hid_controller_t *c)
{
	int i;

	for(i = 0; i < c->main.num_entries; i++)
	{
		if(c->main.entries[i].controller_state & 1)
		{
			cst = &c->main;
			last_stamp = 0;
			return 0;
		}
	}
	return 1;
}

// swizling

static int pdep(uint32_t mask, uint32_t value)
{
	uint32_t out = 0;
	for (int shift = 0; shift < 32; shift++)
	{
		uint32_t bit = 1u << shift;
		if (mask & bit)
		{
			if (value & 1)
				out |= bit;
			value >>= 1;
		}
	}
	return out;
}

static uint32_t swizzle_x(uint32_t v) { return pdep(~0x7B4u, v); }
static uint32_t swizzle_y(uint32_t v) { return pdep(0x7B4, v); }

static void init_swizzle()
{
	int x, y;
	int i = 0;
	uint32_t offs_x0 = swizzle_x(0);
	uint32_t offs_y = swizzle_y(0);
	uint32_t x_mask = swizzle_x(~0u);
	uint32_t y_mask = swizzle_y(~0u);
	uint32_t offs_x;

	for(y = 0; y < 128; y++)
	{
		offs_x = offs_x0;
		for(x = 0; x < 128; x++)
		{
			swizzle[i++] = offs_y + offs_x;
			offs_x = (offs_x - x_mask) & x_mask;
		}
		offs_y = (offs_y - y_mask) & y_mask;
	}
}

static void place_tile(uint32_t *dst, uint32_t *src)
{
	int x, y, i;

	i = 0;
	for(y = 0; y < 128; y++)
	{
		for(x = 0; x < 128; x++)
		{
			dst[swizzle[i++]] = *src;
			src++;
		}
		src += SCREENWIDTH - 128;
	}
}
#endif

void S_HandleEvents(void (*cb)(int))
{
#ifdef LINUX
	SDL_Event SDLevent;
	while(SDL_PollEvent(&SDLevent))
	{
		switch(SDLevent.type)
		{
			case SDL_QUIT:
				stopped = 1;
			break;
			case SDL_KEYDOWN:
				switch(SDLevent.key.keysym.sym)
				{
					case SDLK_UP:
						cb(AKEY_UP);
					break;
					case SDLK_DOWN:
						cb(AKEY_DOWN);
					break;
					case SDLK_LEFT:
						cb(AKEY_LEFT);
					break;
					case SDLK_RIGHT:
						cb(AKEY_RIGHT);
					break;
					case SDLK_RETURN:
						cb(AKEY_OK);
					break;
					case SDLK_ESCAPE:
						cb(AKEY_KO);
					break;
					case SDLK_SPACE:
						cb(AKEY_OPTIONS);
					break;
				}
			break;
		}
	}
#else
	if(cst)
	{
		// get keys
		int i;
		int lost = 1;
		int read = 0;
		uint64_t btn = 0;

		for(i = 0; i < cst->num_entries; i++)
		{
			if(cst->entries[i].controller_state & 1)
			{
				lost = 0;
				if(cst->entries[i].timestamp > last_stamp)
				{
					read++;
					btn |= cst->entries[i].button_state;
				}
			}
		}

		if(lost)
			cst = NULL;
		if(read)
		{
			// got valid input
			uint64_t change = buttons ^ btn;

			// detect buttons change
			if(change)
			{
				// check only positive changes
				uint64_t bcombo = change & btn;
				// up
				if(bcombo & (SWBTN(21) | SWBTN(17) | SWBTN(13)))
					cb(AKEY_UP);
				// down
				if(bcombo & (SWBTN(23) | SWBTN(19) | SWBTN(15)))
					cb(AKEY_DOWN);
				// left
				if(bcombo & (SWBTN(20) | SWBTN(16) | SWBTN(12)))
					cb(AKEY_LEFT);
				// right
				if(bcombo & (SWBTN(22) | SWBTN(18) | SWBTN(14)))
					cb(AKEY_RIGHT);
				// A
				if(bcombo & SWBTN(0))
					cb(AKEY_OK);
				// B
				if(bcombo & SWBTN(1))
					cb(AKEY_KO);
				// options
				if(bcombo & (SWBTN(10) | SWBTN(11)))
					cb(AKEY_OPTIONS);
			}

			buttons = btn;
		}
	} else
	{
		// scan for controller
		int i;
		hid_controller_t *controller = hmem->controllers;

		for(i = 0; i < 10; i++)
		{
			if(!check_presence(controller))
				break;
			controller++;
		}
	}
#endif
}

void S_UpdateScreen()
{
#ifdef LINUX
	int i;
	color_t *src = framebuffer;
	color_t *dst = screen->pixels;

	if(SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

//	memcpy(screen->pixels, framebuffer, SCREENWIDTH * SCREENHEIGHT * sizeof(color_t));
	for(i = 0; i < SCREENWIDTH * SCREENHEIGHT; i++)
	{
		dst->channel.r = src->channel.b;
		dst->channel.g = src->channel.g;
		dst->channel.b = src->channel.r;
		dst->channel.a = src->channel.a;
		dst++;
		src++;
	}

	SDL_Flip(screen);
	if(SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);
#else
	int x, y, i;
	result_t r;
	uint32_t handle_idx;
	uint32_t *src = (uint32_t*)framebuffer;
	uint32_t *dst;

	// vsync
	svcWaitSynchronization(&handle_idx, &vsync, 1, 33333333);
	svcResetSignal(vsync);
	// get buffer
	r = surface_dequeue_buffer(&vidsurf, &dst);
	if(r || !dst)
	{
		printf("S_UpdateScreen: surface_dequeue_buffer failed 0x%08X\n", r);
		return;
	}
	// copy pixels
	for(y = 0; y < 6; y++)
	{
		for(x = 0; x < 10; x++)
		{
			place_tile(dst, src);
			src += 128;
			dst += 128 * 128;
		}
		src += 127 * SCREENWIDTH;
	}
	// update buffer
	r = surface_queue_buffer(&vidsurf);
	if(r)
	{
		printf("S_UpdateScreen: surface_queue_buffer failed 0x%08X", r);
		stopped = 1;
	}
#endif
}

int S_Init()
{
#ifdef LINUX
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("- SDL_Init error\n");
		return 1;
	}
	if(!(screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, 32, SDL_HWSURFACE)))
	{
		SDL_Quit();
		printf("- SDL_SetVideoMode failed\n");
		return 1;
	}

	if(SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);
	framebuffer = malloc(SCREENWIDTH * SCREENHEIGHT * sizeof(color_t));
#else
	result_t r;

	// init controls
	if(S_InitHid())
		return 1;

	// init video
	r = gpu_initialize();
	if(r)
		return 2;
	r = vi_init();
	if(r)
		return 3;
	r = display_init();
	if(r)
		return 4;
	r = display_open_layer(&vidsurf);
	if(r)
		return 5;
	r = display_get_vsync_event(&vsync);
	if(r)
		return 6;
	// init swizzle table
	init_swizzle();
#endif
	return 0;
}

void S_Deinit()
{
#ifdef LINUX
	SDL_Quit();
#else
	// deinit screen and HID
	display_finalize();
	vi_finalize();
	gpu_finalize();
	hid_finalize();
#endif
}

int S_ReadFile(const char *path, void *buff, int maxsize)
{
#ifdef LINUX
	int size;
	FILE *f;

	f = fopen(path, "rb");
	if(!f)
		return -404;

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);

	if(!size || size > maxsize)
	{
		fclose(f);
		return -1;
	}

	fread(buff, 1, size, f);

	fclose(f);

	return size;
#else
	return http_get_file(path, buff, (uint64_t)maxsize);
#endif
}

void S_FreeMemory()
{
#ifdef LINUX
	omax = 0;
#endif
	ocur = 0;
}

void *S_GetMemory(int size)
{
#ifdef LINUX
	void *ret;

	if(!optmem)
	{
		optmem = malloc(4096);
		if(optmem)
		{
			omax = 4096;
			ocur = size;
		}
		return optmem;
	}

	if(ocur + size > omax)
	{
		void *tmp;

		tmp = realloc(optmem, omax + 4096);
		if(!tmp)
			return NULL;
		omax += 4096;
		optmem = tmp;
	}

	ret = optmem + ocur;
	ocur += size;
	return ret;
#else
	void *ret;

	if(ocur + size > sizeof(optmem))
		return NULL;

	ret = optmem + ocur;
	ocur += size;

	return ret;
#endif
}

#ifndef LINUX
int S_InitHid()
{
	result_t r;

	r = hid_init();
	if(r)
		return 1;

	cst = NULL;
	last_stamp = 0;
	buttons = 0;

	hmem = hid_get_shared_memory();
	if(!hmem)
		return 1;

	return 0;
}
#endif

