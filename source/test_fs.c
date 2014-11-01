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
	print(GFX_TOP, "fsInit - [%u]\n", initResult);
}

void FS_TestSdmcOpen()
{
	sdmcArchive = (FS_archive) { 0x00000009, { PATH_EMPTY, 1, (u8*) "" } };

	unsigned int openResult = FSUSER_OpenArchive(NULL, &sdmcArchive);
	print(GFX_TOP, "FSUSER_OpenArchive - [%u]\n", openResult);
}

void FS_TestSdmcOpenFile()
{
	Handle fileHandleC, fileHandleW, fileHandleR;
	FS_path filePath = FS_makePath(PATH_CHAR, "/new_file.txt");

	unsigned int openResultC = FSUSER_OpenFile(NULL, &fileHandleC, sdmcArchive, filePath, 2, 0);
	print(GFX_TOP, "FSUSER_OpenFile (create flag) - '%s' - [%u]\n", filePath.data, openResultC);
	svcCloseHandle(fileHandleC);

	unsigned int openResultW = FSUSER_OpenFile(NULL, &fileHandleW, sdmcArchive, filePath, 1, 0);
	print(GFX_TOP, "FSUSER_OpenFile (write flag) - '%s' - [%u]\n", filePath.data, openResultW);
	svcCloseHandle(fileHandleW);
}

void FS_TestSdmcCreateDir()
{
	FS_path dirPath = FS_makePath(PATH_CHAR, "/new_dir");
	unsigned int createResult = FSUSER_CreateDirectory(NULL, sdmcArchive, dirPath);
	print(GFX_TOP, "FSUSER_CreateDirectory - '%s' - [%u]\n", dirPath.data, createResult);
}

void FS_TestSdmcClose()
{
	unsigned int closeResult = FSUSER_CloseArchive(NULL, &sdmcArchive);
	print(GFX_TOP, "FSUSER_CloseArchive - [%u]\n", closeResult);
}

void FS_TestExit()
{
	unsigned int exitResult = fsExit();
	print(GFX_TOP, "fsExit - [%u]", exitResult);
}
