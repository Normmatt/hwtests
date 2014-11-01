#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>

#include "output.h"
#include "test_fs.h"

static int testCounter = 0;
static void (*tests[]) (void) = {
	FS_TestAll
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

	APP_STATUS status;
	while ((status = aptGetStatus()) != APP_EXITING) {
		if (status == APP_RUNNING) {
			drawFrames();

			hidScanInput();
			if (hidKeysDown() & KEY_B) {
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

		} else if (status == APP_SUSPENDING) {
			aptReturnToMenu();
		} else if (status == APP_SLEEPMODE) {
			aptWaitStatusEvent();
			break;
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
