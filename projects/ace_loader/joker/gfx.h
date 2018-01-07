
// main area
#define GFX_COLOR_BACKGROUND	0xFF2D2D2D

// global
#define GFX_TEXT_COLOR		0xFFFFFFFF
#define GFX_TEXT_COLOR_SEL	0xFFc8fd02

// main line
#define GFX_COLOR_LINE		0xFFFFFFFF
#define GFX_LAYOUT_LINEX	30
#define GFX_LAYOUT_LINEY	647
#define GFX_LAYOUT_LINEW	1220

// main help
#define GFX_MAIN_HELPX	850
#define GFX_MAIN_HELPY	665

// slot layout
#define GFX_COLOR_SHADOW	0xFF000000
#define GFX_LAYOUT_XCOUNT	4
#define GFX_LAYOUT_YCOUNT	2
#define GFX_LAYOUT_STARTX	56
#define GFX_LAYOUT_STARTY	32
#define GFX_LAYOUT_STEPX	(GFX_ICON_SIZE + 48)
#define GFX_LAYOUT_STEPY	(GFX_ICON_SIZE + 48)

// icon slot
#define GFX_COLOR_SLOTBACK	0xFF323232
#define GFX_COLOR_SLOTEDGE	0xFF404040
#define GFX_COLOR_SLOTGRAD1	0xFF2B2B2B
#define GFX_COLOR_SLOTGRAD2	0xFF222222
#define GFX_ICON_EDGE	3
#define GFX_ICON_SIZE	256

// icon selector
#define GFX_COLOR_SLOTSEL	0xFFBA861C
#define GFX_SEL_SPACE	4
#define GFX_SEL_EDGE	5

// options
#define GFX_COLOR_OPT_BACK	0xFF221A13
#define GFX_COLOR_OPT_BG	0xFF464646
#define GFX_COLOR_OPT_BGRAD	0xFF4B4B4B
#define GFX_COLOR_OPT_SEL	0xFF433f3a
#define GFX_OPT_STARTX	120
#define GFX_OPT_WIDTH	1040
#define GFX_OPT_LINEX	150
#define GFX_OPT_LINEW	980
#define GFX_OPT_LIN1Y	140
#define GFX_OPT_LIN2Y	647
#define GFX_OPT_GRADY	141
#define GFX_OPT_GRADW	360
#define GFX_OPT_GRADH	506
#define GFX_OPT_GRADHG	55
#define GFX_OPT_TITLEX	310
#define GFX_OPT_TITLEY	40
#define GFX_OPT_INFOY	90
#define GFX_OPT_ICONX	190
#define GFX_OPT_ICONY	20
#define GFX_OPT_ICONS	100
#define GFX_OPT_HELPX	900
#define GFX_OPT_HELPY	665
#define GFX_OPT_OPTX	196
#define GFX_OPT_OPTY	200
#define GFX_OPT_OPTH	50
#define GFX_OPT_OPTS	14
#define GFX_OPT_OPTSX	180
#define GFX_OPT_OPTSW	285
#define GFX_OPT_NOPTX	500
#define GFX_OPT_NOPTY	360
// suboptions
#define GFX_SOPT_BACKX	480
#define GFX_SOPT_BACKY	141
#define GFX_SOPT_BACKW	680
#define GFX_SOPT_BACKH	506
#define GFX_SOPT_OPTX	530
#define GFX_SOPT_OPTY	200
#define GFX_SOPT_OPTH	50
#define GFX_SOPT_SELW	600

// message
#define GFX_MESSAGE_BACK 0xFF464646
#define GFX_MESSAGE_TEXT 0xFFFFFFFF
#define GFX_MESSAGE_BOXX	255
#define GFX_MESSAGE_BOXY	189
#define GFX_MESSAGE_BOXW	770
#define GFX_MESSAGE_BOXH	342
#define GFX_MESSAGE_ICONX	315
#define GFX_MESSAGE_ICONY	238
#define GFX_MESSAGE_ICONSIZE	170
#define GFX_MESSAGE_SELY	460
#define GFX_MESSAGE_CONTX	(SCREENWIDTH / 2)
#define GFX_MESSAGE_CONTX2	((SCREENWIDTH / 2) + (GFX_MESSAGE_ICONSIZE / 2) + 16)
#define GFX_MESSAGE_CONTY	475

// blending
#define GFX_Blend(d, s, a)	(d) = (((int)(d)*(int)(255-(a)) + (int)(s)*(int)(a)) / 255)

typedef struct
{
	color_t palette[256];
	uint8_t pixels[GFX_ICON_SIZE*GFX_ICON_SIZE];
} icon8bit_t;

// simple GFX
void GFX_HideScreen(int hide);
void GFX_ClearColor(color_t col);
void GFX_RectClear(int x, int y, int w, int h, color_t col);
void GFX_RectHGradient(int x, int y, int w, int h, color_t col, uint8_t start, int16_t step);
void GFX_RectVGradient(int x, int y, int w, int h, color_t col, uint8_t start, int16_t step);
void GFX_RectPixels8Bit(int x, int y, int w, int h, icon8bit_t *icon);

// combined GFX
void GFX_IconSlot(int x, int y);
void GFX_Selection(int x, int y, int w, int h, color_t col);

// very specific GFX
void GFX_MiniPixels8Bit(int x, int y, int w, int h, icon8bit_t *icon, int nw, int nh);

// BMP loading
int GFX_IconFromBMP(void *buff, icon8bit_t *icon);

