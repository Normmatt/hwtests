#include "test.h"

#include <3ds.h>

#include "output.h"

void PrintSuccess(std::string group, std::string name, bool val)
{
    print(GFX_TOP, "%s: %s - %s\n", group.c_str(), name.c_str(), val ? "SUCCESS" : "FAILURE");
}
