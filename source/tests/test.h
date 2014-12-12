#pragma once

#include <functional>

// If the condition fails, return false
#define SoftAssert(cond) do { if (!(cond)) { return false; } } while (0)

void PrintSuccess(std::string group, std::string name, bool val);

template <typename T>
bool Test(std::string group, std::string name, T result, T expected)
{
    PrintSuccess(group, name, result == expected);
    return result == expected;
}
