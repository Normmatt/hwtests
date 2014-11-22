#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <3ds.h>
#include "text.h"

#include "font.h"

//this code is not meant to be readable
int drawCharacter(u8* fb, font_s* font, char c, s16 x, s16 y, u16 w, u16 h)
{
	charDesc_s* cd = &font->desc[(int)c];

	if (!cd->data)
		return 0;

	x += cd->xo; y += font->height - cd->yo - cd->h;

	if (x < 0 || x + cd->w >= w || y < -cd->h || y >= h + cd->h)
		return 0;

	u8* charData = cd->data;
	s16 cy = y, ch = cd->h, cyo = 0;

	if (y < 0) {
		cy = 0;
		cyo = -y;
		ch = cd->h-cyo;
	} else if (y + ch > h) {
		ch = h - y;
	}

	fb += (x * h + cy) * 3;
	const u8 r = font->color[0];
	const u8 g = font->color[1];
	const u8 b = font->color[2];

	int i, j;
	for (i = 0; i < cd->w; i++) {
		charData += cyo;
		for(j = 0; j < ch; j++) {
			u8 v = *(charData++);
			if (v) {
				fb[0] = (fb[0] * (0xFF - v) + (b * v)) >> 8;
				fb[1] = (fb[1] * (0xFF - v) + (g * v)) >> 8;
				fb[2] = (fb[2] * (0xFF - v) + (r * v)) >> 8;
			}
			fb += 3;
		}
		charData += (cd->h - (cyo + ch));
		fb += (h - ch) * 3;
	}
	return cd->xa;
}

void drawString(u8* fb, font_s* f, const char* str, s16 x, s16 y, u16 w, u16 h)
{
	if (!f || !fb || !str)
		return;

	int k, dx = 0, dy = 0;
	int length = strlen(str);
	for (k = 0; k < length; k++)
	{
		dx += drawCharacter(fb, f, str[k], x + dx, y + dy, w, h);
		if(str[k]=='\n') {
			dx = 0;
			dy -= f->height;
		}
	}
}

void gfxDrawText(gfxScreen_t screen, gfx3dSide_t side, font_s* font, const char* str, s16 x, s16 y)
{
	if(!str)
		return;
	if(!font)
		font = &fontDefault;

	u16 fbWidth, fbHeight;
	u8* fbAdr = gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

	drawString(fbAdr, font, str, y, x, fbHeight, fbWidth);
}
