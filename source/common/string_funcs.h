#pragma once

#include <string>

namespace Common {

std::string FormatString(const char* format, ...);

/**
 * Returns the number of lines (broken by '\n') in the string
 */
int CountLines(const std::string& str);

/**
 * Deletes the first line (broken by '\n') from the string
 */
void DeleteFirstLine(std::string* str);

}
