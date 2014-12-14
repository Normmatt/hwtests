#pragma once

#include <string>

typedef void (*TestCaller)(void);

void SoftAssertLog(const std::string& function, int line, const std::string& condition);

// If the condition fails, return false
#define SoftAssert(cond) \
    do { \
        if (!(cond)) { \
            SoftAssertLog(__PRETTY_FUNCTION__, __LINE__, #cond); \
            return false; \
        } \
    } while (0)

void PrintSuccess(const std::string& group, const std::string& name, bool val);

template <typename T>
bool Test(const std::string& group, const std::string& name, T result, T expected)
{
    PrintSuccess(group, name, result == expected);
    return result == expected;
}
