#pragma once

#include <string>

#include <3ds.h>

#include "font.h"

struct Rect {
    int w, h;
};

Rect GetScreenSize(gfxScreen_t screen);

int DrawCharacter(u8* fb, font_s* f, char c, s16 x, s16 y, u16 w, u16 h);
void DrawString(u8* fb, font_s* f, const std::string& str, s16 x, s16 y, u16 w, u16 h);
void DrawText(gfxScreen_t screen, gfx3dSide_t side, font_s* f, const std::string& str, s16 x, s16 y);
void FillScreen(gfxScreen_t screen, u8 bg_r, u8 bg_g, u8 bg_b);
