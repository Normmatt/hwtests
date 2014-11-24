#pragma once

#include <functional>

// If the condition fails, return false
#define SoftAssert(cond) do { if (!(cond)) { return false; } } while (0)

void Test(std::string group, std::string name, std::function<bool (void)> test);

void TestResult(std::string group, std::string name, std::function<int (void)> test);
