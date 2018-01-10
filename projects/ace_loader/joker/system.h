
typedef union
{
	struct
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	} channel;
	uint32_t value;
	int32_t vals;
} color_t;

extern int stopped;
#ifdef LINUX
extern color_t *framebuffer;
#else
extern color_t framebuffer[1280 * 768];
#endif

enum
{
	AKEY_UP,
	AKEY_DOWN,
	AKEY_LEFT,
	AKEY_RIGHT,
	AKEY_OK,
	AKEY_KO,
	AKEY_OPTIONS,
	// virtual keys
	AKEY_DRAWSEL, // redraw current selection
};

int S_Init();
void S_Deinit();
void S_UpdateScreen();
void S_HandleEvents(void (*cb)(int));
int S_ReadFile(const char *path, void *buff, int maxsize);

void S_FreeMemory();
void *S_GetMemory(int size);

#ifndef LINUX
int S_InitHid();
#endif
