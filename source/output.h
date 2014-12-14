#pragma once

#include <string>

#include <3ds.h>

void InitOutput();

void DrawBuffers();

/// Prints `text` to `screen`.
void Print(gfxScreen_t screen, const std::string& text);

/// Prints `text` to `screen`, and logs it in the log file.
void Log(gfxScreen_t screen, const std::string& text);

/// Logs `text` to the log file.
void LogToFile(const std::string& text);

void ClearScreen(gfxScreen_t screen, u8 bg_r, u8 bg_g, u8 bg_b);
void ClearScreens();

void DeinitOutput();
