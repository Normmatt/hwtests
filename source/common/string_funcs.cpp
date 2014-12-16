#include "string_funcs.h"

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace Common {

std::string FormatString(const char* format, ...)
{
    va_list arguments;
    char *va_str;

    va_start(arguments, format);
    vasprintf(&va_str, format, arguments);
    va_end(arguments);

    std::string out_str(va_str);
    free(va_str);
    
    return out_str;
}

int CountLines(const std::string& str)
{
    if (str.empty())
        return 0;

    return 1 + std::count_if(str.begin(), str.end(), [](char c) { return c == '\n'; });
}

void DeleteFirstLine(std::string* str)
{
    if (str->empty())
        return;
    
    size_t linebreak = str->find_first_of('\n');
    
    if (linebreak == std::string::npos || linebreak + 1 > str->length()) {
        *str = {};
        return;
    }
    
    *str = str->substr(linebreak + 1);
}

}
