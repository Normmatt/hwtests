#pragma once

#include <functional>

void Test(std::string group, std::string name, std::function<bool (void)> test);

void TestResult(std::string group, std::string name, std::function<int (void)> test);
