#include "test_fs.h"

#include <3ds.h>

#include "output.h"

static FS_archive sdmcArchive;

void FS_TestAll()
{
	FS_TestInit();
	FS_TestSdmcOpen();
	FS_TestSdmcOpenFile();
	FS_TestSdmcCreateDir();
	FS_TestSdmcClose();
	FS_TestExit();
}

void FS_TestInit()
{
	unsigned int initResult = fsInit();
	print("fsInit - [%u]\n", initResult);
}

void FS_TestSdmcOpen()
{
	sdmcArchive = (FS_archive) { 0x00000009, { PATH_EMPTY, 1, (u8*) "" } };

	unsigned int openResult = FSUSER_OpenArchive(NULL, &sdmcArchive);
	print("FSUSER_OpenArchive - [%u]\n", openResult);
}

void FS_TestSdmcOpenFile()
{
	Handle fileHandle;
	FS_path filePath = FS_makePath(PATH_CHAR, "/new_file.txt");
	unsigned int openResult = FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, filePath, 2, 0);
	print("FSUSER_OpenFile - [%u]\n", openResult);
	svcCloseHandle(fileHandle);
}

void FS_TestSdmcCreateDir()
{
	unsigned int createResult = FSUSER_CreateDirectory(NULL, sdmcArchive, FS_makePath(PATH_CHAR, "/new_dir"));
	print("FSUSER_CreateDirectory - [%u]\n", createResult);
}

void FS_TestSdmcClose()
{
	unsigned int closeResult = FSUSER_CloseArchive(NULL, &sdmcArchive);
	print("FSUSER_CloseArchive - [%u]\n", closeResult);
}

void FS_TestExit()
{
	unsigned int exitResult = fsExit();
	print("fsExit - [%u]", exitResult);
}
