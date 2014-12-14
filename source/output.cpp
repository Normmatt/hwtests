#include <3ds.h>

#include "output.h"

#include <cmath>
#include <fstream>

#include "draw.h"
#include "common/string_funcs.h"

static FILE* log_file;

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

static void DrawBuffer(gfxScreen_t screen)
{
    Rect screen_size = GetScreenSize(screen);
    std::string& text_buffer = GetTextBuffer(screen);

    int lines = Common::CountLines(text_buffer);
    while (lines > (screen_size.h / fontDefault.height - 3)) {
        Common::DeleteFirstLine(&text_buffer);
        lines--;
    }
    DrawText(screen, GFX_LEFT, nullptr, text_buffer, screen_size.h - fontDefault.height * 3, 10);
}

void InitOutput()
{
    sdmcInit();
    log_file = fopen("hwtest_log.txt", "w");
}

void DrawBuffers()
{
    FillScreen(GFX_TOP, 0x00, 0x66, 0x88);
    DrawBuffer(GFX_TOP);
    
    FillScreen(GFX_BOTTOM, 0x00, 0x00, 0x00);
    DrawBuffer(GFX_BOTTOM);
    
    gfxFlushBuffers();
    gfxSwapBuffers();
}

void ClearScreen(gfxScreen_t screen, u8 bg_r, u8 bg_g, u8 bg_b)
{
    FillScreen(screen, bg_r, bg_g, bg_b);
    GetTextBuffer(screen).clear();
    gfxFlushBuffers();
    gfxSwapBuffers();
}

void ClearScreens()
{
    ClearScreen(GFX_TOP, 0x00, 0x66, 0x88);
    ClearScreen(GFX_BOTTOM, 0x00, 0x00, 0x00);
}

void Print(gfxScreen_t screen, const std::string& text)
{
    GetTextBuffer(screen) += text;
    DrawBuffers();
}

void Log(gfxScreen_t screen, const std::string& text)
{
    Print(screen, text);
    LogToFile(text);
}

void LogToFile(const std::string& text)
{
    svcOutputDebugString(text.c_str(), text.length());
    fprintf(log_file, "%s", text.c_str());
}

void DeinitOutput()
{
    fclose(log_file);
    sdmcExit();
}
