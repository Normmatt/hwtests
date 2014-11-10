#include "test_fs.h"

#include <3ds.h>

#include "output.h"

static void FS_TestSdmc()
{
	FS_archive sdmcArchive = (FS_archive) { 0x00000009, { PATH_EMPTY, 1, (u8*) "" } };

	// Open SDMC
	unsigned int openArchiveResult = FSUSER_OpenArchive(NULL, &sdmcArchive);
	print(GFX_TOP, "SDMC: Opening SDMC Archive - [%u]\n", openArchiveResult);

	Handle dirHandle;
	FS_path dirPath = FS_makePath(PATH_CHAR, "/new_dir");

	// Create Directory
	unsigned int createDirResult = FSUSER_CreateDirectory(NULL, sdmcArchive, dirPath);
	print(GFX_TOP, "SDMC: Creating Directory '%s' - [%u]\n", dirPath.data, createDirResult);

	// Open Directory
	unsigned int openDirResult = FSUSER_OpenDirectory(NULL, &dirHandle, sdmcArchive, dirPath);
	print(GFX_TOP, "SDMC: Opening Directory '%s' - [%u]\n", dirPath.data, openDirResult);

	Handle fileHandle;
	FS_path filePath = FS_makePath(PATH_CHAR, "/new_dir/new_file.txt");

	// Open File
	unsigned int openFileResult = FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, filePath, FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
	print(GFX_TOP, "SDMC: Opening File '%s' - [%u]\n", filePath.data, openFileResult);

	// Write File
	u32 bytesWritten;
	const char* stringWritten = "A string\n";
    unsigned int writeFileResult = FSFILE_Write(fileHandle, &bytesWritten, 0, stringWritten, strlen(stringWritten), FS_WRITE_FLUSH);
	print(GFX_TOP, "SDMC: Writing Data to File .. - [%u]\n", writeFileResult);

	// Check File Size
	u64 fileSize;
	unsigned int getFileSizeResult = FSFILE_GetSize(fileHandle, &fileSize);
	print(GFX_TOP, "SDMC: Getting Size of File .. - [%u]\n", getFileSizeResult);

	// Verify File Size
	print(GFX_TOP, "SDMC: Verifying Size with Written Bytes - %s\n", fileSize == bytesWritten ? "SUCCESS" : "FAILURE");

	// Close File
	unsigned int closeFileResult = FSFILE_Close(fileHandle);
	print(GFX_TOP, "SDMC: Closing File .. - [%u]\n", closeFileResult);

	// Close Directory
	unsigned int closeDirResult = FSDIR_Close(dirHandle);
	print(GFX_TOP, "SDMC: Closing Directory .. - [%u]\n", closeDirResult);

	// Delete File
	unsigned int deleteFileResult = FSUSER_DeleteFile(NULL, sdmcArchive, filePath);
	print(GFX_TOP, "SDMC: Deleting File .. - [%u]\n", deleteFileResult);	

	// Delete Directory
	unsigned int deleteDirResult = FSUSER_DeleteDirectory(NULL, sdmcArchive, dirPath);
	print(GFX_TOP, "SDMC: Deleting Directory .. - [%u]\n", deleteDirResult);

	// Close SDMC
	unsigned int closeArchiveResult = FSUSER_CloseArchive(NULL, &sdmcArchive);
	print(GFX_TOP, "SDMC: Closing SDMC Archive - [%u]\n", closeArchiveResult);
}


void FS_TestAll()
{
	unsigned int initResult = fsInit();
	print(GFX_TOP, "fsInit - [%u]\n", initResult);

	FS_TestSdmc();

	unsigned int exitResult = fsExit();
	print(GFX_TOP, "fsExit - [%u]", exitResult);
}
