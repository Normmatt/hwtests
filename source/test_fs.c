#include "test_fs.h"

#include <3ds.h>

#include "output.h"

static FS_archive sdmcArchive;

void FS_TestAll()
{
	FS_TestInit();
	FS_TestSdmcOpen();
	FS_TestSdmcCreateDir();
	FS_TestSdmcClose();
}

void FS_TestInit()
{
	print("fsInit %08X\n", (unsigned int)
		fsInit()
	);
}

void FS_TestSdmcOpen()
{
	sdmcArchive = (FS_archive) { 0x00000009, { PATH_EMPTY, 1, (u8*) "" } };

	print("FSUSER_OpenArchive %08X\n", (unsigned int)
		FSUSER_OpenArchive(NULL, &sdmcArchive)
	);
}

void FS_TestSdmcCreateDir()
{
	print("FSUSER_CreateDirectory %08X\n", (unsigned int)
		FSUSER_CreateDirectory(NULL, sdmcArchive, FS_makePath(PATH_CHAR, "/new_dir"))
	);
}

void FS_TestSdmcClose()
{
	print("FSUSER_CloseArchive %08X\n", (unsigned int)
		FSUSER_CloseArchive(NULL, &sdmcArchive)
	);
}
