#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>

#include "output.h"
#include "tests/fs/fs.h"
#include "tests/cpu/cputests.h"

static unsigned int testCounter = 0;
static void (*tests[]) (void) = {
    FS::TestAll,
    CPU::Integer::TestAll
};

int main()
{
    srvInit();
    aptInit();
    hidInit(NULL);
    gfxInit();
    gfxSet3D(false);

    clearScreens();
    print(GFX_TOP, "Press A to begin...\n");

    while (aptMainLoop()) {
        drawFrames();

        hidScanInput();
        if (hidKeysDown() & KEY_START) {
            break;
        } else if (hidKeysDown() & KEY_A) {
            clearScreen(GFX_TOP);

            if (testCounter < (sizeof(tests) / sizeof(tests[0]))) {
                tests[testCounter]();
                testCounter++;
            } else {
                break;
            }

            print(GFX_TOP, "\n");
            print(GFX_TOP, "Press A to continue...\n");
        }

        gspWaitForEvent(GSPEVENT_VBlank0, false);
    }

    clearScreens();
    gfxExit();
    hidExit();
    aptExit();
    srvExit();
    return 0;
}
