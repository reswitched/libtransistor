
enum
{
	FONT_BIG,
	FONT_MEDIUM,
	FONT_SMALL,
};

void kfn_setfont(int font, color_t color);
int kfn_height();

void kfn_putchar(int x, int y, char in);
void kfn_write(int x, int y, const char *text);
int kfn_textwidth(const char *text);

