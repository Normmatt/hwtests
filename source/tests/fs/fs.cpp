#include <3ds.h>

#include "tests/test.h"
#include "tests/fs/fs.h"
#include "tests/fs/fs_sdmc.h"

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
