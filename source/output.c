#include "output.h"

#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <3ds.h>

#include "text.h"

char superStr[8192];
static int cnt;

static int countLines(const char* str)
{
	if (!str)
		return 0;

	int cnt = 1;
	while (*str == '\n' ? ++cnt : *str)
		str++;
	return cnt;
}

static void cutLine(char* str)
{
	if (!str || !*str)
		return;

	char* str2 = str;
	while ((*str2) && (*(str2 + 1)) && (*str2 != '\n'))
		str2++;
	str2++;

	memmove(str, str2, strlen(str2) + 1);
}

void drawFrame()
{
	u8* bufAdr = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	int x, y;
	for (x = 1; x < 400; x++) {
		for (y = 1; y < 240; y++) {
			u32 v=(y + x * 240) * 3;
			bufAdr[v]   = 0x88;
			bufAdr[v+1] = 0x66;
			bufAdr[v+2] = 0x00;
		}
	}

	x = countLines(superStr);
	while (x > (240 / fontDefault.height - 3)) {
		cutLine(superStr);
		x--;
	}
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, superStr, 240 - fontDefault.height * 3, 10);
	cnt++;

	gfxFlushBuffers();
	gfxSwapBuffers();
}

void print(const char* format, ...)
{
	va_list arguments;
	char new_str[512];

	va_start(arguments, format);
	vsprintf(new_str, format, arguments);
	va_end(arguments);

	sprintf(&superStr[strlen(superStr)], new_str);
	svcOutputDebugString(new_str, strlen(new_str));

	drawFrame();
}
