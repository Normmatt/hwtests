#include <3ds.h>

#include "output.h"
#include "tests/test.h"
#include "tests/fs/fs.h"
#include "tests/cpu/cputests.h"

static unsigned int test_counter = 0;
static TestCaller tests[] = {
    FS::TestAll,
    CPU::Integer::TestAll
};

int main(int argc, char** argv)
{
    srvInit();
    aptInit();
    hidInit(NULL);
    gfxInit();
    gfxSet3D(false);
    fsInit();

    ClearScreens();
    Print(GFX_TOP, "Press A to begin...\n");

    while (aptMainLoop()) {
        DrawFrames();

        hidScanInput();
        if (hidKeysDown() & KEY_START) {
            break;
        } else if (hidKeysDown() & KEY_A) {
            ClearScreen(GFX_TOP);

            if (test_counter < (sizeof(tests) / sizeof(tests[0]))) {
                tests[test_counter]();
                test_counter++;
            } else {
                break;
            }

            Print(GFX_TOP, "\n");
            Print(GFX_TOP, "Press A to continue...\n");
        }

        gspWaitForEvent(GSPEVENT_VBlank0, false);
    }

    ClearScreens();
    fsExit();
    gfxExit();
    hidExit();
    aptExit();
    srvExit();
    return 0;
}
