#include "output.h"

#include <cmath>

#include <3ds.h>

#include "text.h"
#include "common/string_funcs.h"

static std::string buffer_top;
static std::string buffer_bottom;

static std::string& GetTextBuffer(gfxScreen_t screen)
{
    switch (screen) {
        case GFX_TOP:    return buffer_top;
        case GFX_BOTTOM: return buffer_bottom;
    }
    return buffer_top;
}

static void DrawFrame(gfxScreen_t screen, char b, char g, char r)
{
    int screen_height = 240;
    int screen_width = (screen == GFX_TOP) ? 400 : 320;
    std::string& text_buffer = GetTextBuffer(screen);

    u8* fb_addr = gfxGetFramebuffer(screen, GFX_LEFT, nullptr, nullptr);
    for (int i = 0; i < screen_width * screen_height * 3; i += 3) {
        fb_addr[i]   = b;
        fb_addr[i+1] = g;
        fb_addr[i+2] = r;
    }

    int lines = Common::CountLines(text_buffer);
    while (lines > (screen_height / fontDefault.height - 3)) {
        Common::DeleteFirstLine(&text_buffer);
        lines--;
    }
    gfxDrawText(screen, GFX_LEFT, nullptr, text_buffer, screen_height - fontDefault.height * 3, 10);
}

void DrawFrames()
{
    DrawFrame(GFX_TOP, 0x88, 0x66, 0x00);
    DrawFrame(GFX_BOTTOM, 0x00, 0x00, 0x00);
    gfxFlushBuffers();
    gfxSwapBuffers();
}

void Print(gfxScreen_t screen, const std::string& text)
{
    GetTextBuffer(screen) += text;
    svcOutputDebugString(text.c_str(), text.length());

    DrawFrames();
}

void ClearScreen(gfxScreen_t screen)
{
    GetTextBuffer(screen).clear();
    DrawFrames();
}

void ClearScreens()
{
    ClearScreen(GFX_TOP);
    ClearScreen(GFX_BOTTOM);
}
