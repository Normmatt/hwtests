#include "draw.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <3ds.h>

#include "font.h"

Rect GetScreenSize(gfxScreen_t screen)
{
    return { (screen == GFX_TOP) ? 400 : 320, 240 };
}

// This code is not meant to be readable -- Smea
int DrawCharacter(u8* fb, font_s* font, char c, s16 x, s16 y, u16 w, u16 h)
{
    Glyph* cd = &font->desc[(int)c];

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

    for (int i = 0; i < cd->w; i++) {
        charData += cyo;
        for (int j = 0; j < ch; j++) {
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

void DrawString(u8* fb, font_s* f, const std::string& str, s16 x, s16 y, u16 w, u16 h)
{
    if (!f || !fb)
        return;

    int dx = 0, dy = 0;
    for (const char& c : str)
    {
        dx += DrawCharacter(fb, f, c, x + dx, y + dy, w, h);
        if (c == '\n') {
            dx = 0;
            dy -= f->height;
        }
    }
}

void DrawText(gfxScreen_t screen, gfx3dSide_t side, font_s* font, const std::string& str, s16 x, s16 y)
{
    if (!font)
        font = &fontDefault;

    u16 fbWidth, fbHeight;
    u8* fbAdr = gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

    DrawString(fbAdr, font, str, y, x, fbHeight, fbWidth);
}

void FillScreen(gfxScreen_t screen, u8 bg_r, u8 bg_g, u8 bg_b)
{
    Rect screen_size = GetScreenSize(screen);
    u8* fb_addr = gfxGetFramebuffer(screen, GFX_LEFT, nullptr, nullptr);
    for (int i = 0; i < screen_size.w * screen_size.h * 3; i += 3) {
        fb_addr[i]   = bg_b;
        fb_addr[i+1] = bg_g;
        fb_addr[i+2] = bg_r;
    }
}
