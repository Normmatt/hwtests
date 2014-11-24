#include "tests/fs_sdmc.h"

#include <3ds.h>

#include "tests/fs.h"
#include "tests/test.h"

namespace FS {

void TestAll()
{
    TestResult("FS", "Initializing service", [&]{
        return fsInit();
    });

    SDMC::TestAll();

    TestResult("FS", "Exiting service", [&]{
        return fsExit();
    });
}

} // namespace
