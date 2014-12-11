#include <3ds.h>

#include "tests/test.h"
#include "tests/fs/fs.h"
#include "tests/fs/fs_sdmc.h"

namespace FS {

void TestAll()
{
    Test("FS", "Initializing service", fsInit(), 0L);

    SDMC::TestAll();

    Test("FS", "Exiting service", fsExit(), 0L);
}

} // namespace
