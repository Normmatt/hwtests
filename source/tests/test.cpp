#include "test.h"

#include <3ds.h>

#include "output.h"
#include "common/string_funcs.h"

void PrintSuccess(const std::string& group, const std::string& name, bool val)
{
    Print(GFX_TOP, Common::FormatString("%s: %s - %s\n", group.c_str(), name.c_str(), val ? "SUCCESS" : "FAILURE"));
}
