#include "test.h"

#include <3ds.h>

#include "output.h"

void Test(std::string group, std::string name, std::function<bool (void)> test)
{
	print(GFX_TOP, "%s: %s - %s\n", group.c_str(), name.c_str(), test() ? "SUCCESS" : "FAILURE");
}

void TestResult(std::string group, std::string name, std::function<int (void)> test)
{
	print(GFX_TOP, "%s: %s - %s\n", group.c_str(), name.c_str(), test() == 0 ? "SUCCESS" : "FAILURE");
}
