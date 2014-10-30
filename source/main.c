#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>

#include "output.h"

int main()
{
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	gfxSet3D(false);

	superStr[0]=0;

	print("fsInit %08X\n", (unsigned int)
		fsInit()
	);

	FS_archive sdmcArchive = { 0x00000009, { PATH_EMPTY, 1, (u8*) "" } };

	print("FSUSER_OpenArchive %08X\n", (unsigned int)
		FSUSER_OpenArchive(NULL, &sdmcArchive)
	);

	APP_STATUS status;
	while ((status=aptGetStatus()) != APP_EXITING) {
		if (status == APP_RUNNING) {
			drawFrame();

			hidScanInput();
			if (hidKeysDown() & KEY_B) {
				break;
			} else if (hidKeysDown() & KEY_A) {
				print("FSUSER_CreateDirectory %08X\n", (unsigned int)
					FSUSER_CreateDirectory(NULL, sdmcArchive, FS_makePath(PATH_CHAR, "/new_dir"))
				);
			}
		}
		else if (status == APP_SUSPENDING) {
			aptReturnToMenu();
		}
		else if (status == APP_SLEEPMODE) {
			aptWaitStatusEvent();
		}
		gspWaitForEvent(GSPEVENT_VBlank0, false);
	}

	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}
