#pragma once

struct charDesc_s {
    char c;
    int x, y, w, h, xo, yo, xa;
    u8* data;
};

struct font_s {
    u8* data;
    charDesc_s* desc;
    u8 height;
    u8 color[3];
};

extern u8 font1Data[];
extern charDesc_s font1Desc[];

extern font_s fontDefault;
