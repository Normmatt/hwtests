#include "output.h"

#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <3ds.h>

#include "text.h"

static char bufferTop[8192];
static char bufferBottom[8192];
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

static void drawFrame(gfxScreen_t screen, char b, char g, char r)
{
	int screenWidth;
	char* textBuffer;
	if (screen == GFX_TOP) {
		screenWidth = 400;
		textBuffer = bufferTop;
	} else {
		screenWidth = 320;
		textBuffer = bufferBottom;
	}

	u8* bufAdr = gfxGetFramebuffer(screen, GFX_LEFT, NULL, NULL);
	int x, y;
	for (x = 1; x < screenWidth; x++) {
		for (y = 1; y < 240; y++) {
			u32 v=(y + x * 240) * 3;
			bufAdr[v]   = b;
			bufAdr[v+1] = g;
			bufAdr[v+2] = r;
		}
	}

	x = countLines(textBuffer);
	while (x > (240 / fontDefault.height - 3)) {
		cutLine(textBuffer);
		x--;
	}
	gfxDrawText(screen, GFX_LEFT, NULL, textBuffer, 240 - fontDefault.height * 3, 10);
	cnt++;
}

void drawFrames()
{
	drawFrame(GFX_TOP, 0x88, 0x66, 0x00);
	drawFrame(GFX_BOTTOM, 0x00, 0x00, 0x00);
	gfxFlushBuffers();
	gfxSwapBuffers();
}

void print(gfxScreen_t screen, const char* format, ...)
{
	char* textBuffer = (screen == GFX_TOP) ? bufferTop : bufferBottom;
	va_list arguments;
	char newStr[512];

	va_start(arguments, format);
	vsprintf(newStr, format, arguments);
	va_end(arguments);

	sprintf(&textBuffer[strlen(textBuffer)], newStr);
	svcOutputDebugString(newStr, strlen(newStr));

	drawFrames();
}

void clearScreen(gfxScreen_t screen)
{
	bufferTop[0] = 0;
	drawFrames();
}

void clearScreens()
{
	clearScreen(GFX_TOP);
	clearScreen(GFX_BOTTOM);
}
