#pragma once

#include <string>

typedef void (*TestCaller)(void);

// If the condition fails, return false
#define SoftAssert(cond) do { if (!(cond)) { return false; } } while (0)

void PrintSuccess(const std::string& group, const std::string& name, bool val);

template <typename T>
bool Test(const std::string& group, const std::string& name, T result, T expected)
{
    PrintSuccess(group, name, result == expected);
    return result == expected;
}
