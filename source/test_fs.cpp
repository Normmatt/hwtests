#include "test_fs.h"

#include <3ds.h>

#include "test.h"

namespace FS {

static bool TestSDMCFileCreateDelete(FS_archive sdmcArchive)
{
    Handle fileHandle;
    const static FS_path filePath = FS_makePath(PATH_CHAR, "/test_file_create_delete.txt");
    
    // Create file (not interested in opening the handle)
    SoftAssert(FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, filePath, FS_OPEN_CREATE | FS_OPEN_WRITE, 0) == 0);
    FSFILE_Close(fileHandle);
    
    // Make sure the new file exists
    SoftAssert(FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, filePath, FS_OPEN_READ, 0) == 0);
    FSFILE_Close(fileHandle);

    SoftAssert(FSUSER_DeleteFile(NULL, sdmcArchive, filePath) == 0);

    // Should fail to make sure the file no longer exists
    SoftAssert(FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, filePath, FS_OPEN_READ, 0) != 0);
    FSFILE_Close(fileHandle);

    return true;
}

static bool TestSDMCFileRename(FS_archive sdmcArchive)
{
    Handle fileHandle;
    const static FS_path filePath = FS_makePath(PATH_CHAR, "/test_file_rename.txt");
    const static FS_path newFilePath = FS_makePath(PATH_CHAR, "/test_file_rename_new.txt");
    
    // Create file (not interested in opening the handle)
    FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, filePath, FS_OPEN_CREATE | FS_OPEN_WRITE, 0);
    FSFILE_Close(fileHandle);
    
    SoftAssert(FSUSER_RenameFile(NULL, sdmcArchive, filePath, sdmcArchive, newFilePath) == 0);
    
    // Should fail to make sure the old file no longer exists
    SoftAssert(FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, filePath, FS_OPEN_READ, 0) != 0);
    FSFILE_Close(fileHandle);
    // Make sure the new file exists
    SoftAssert(FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, newFilePath, FS_OPEN_READ, 0) == 0);
    FSFILE_Close(fileHandle);
    
    SoftAssert(FSUSER_DeleteFile(NULL, sdmcArchive, newFilePath) == 0);
    
    return true;
}

static bool TestSDMCFileWrite(FS_archive sdmcArchive)
{
    Handle fileHandle;
    u32 bytesWritten;
    u64 fileSize;
    
    const static FS_path filePath = FS_makePath(PATH_CHAR, "/test_file_write.txt");
    const static char* stringWritten = "A string\n";
    
    // Create file
    FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, filePath, FS_OPEN_CREATE | FS_OPEN_WRITE, 0);
    
    // Write to file
    SoftAssert(FSFILE_Write(fileHandle, &bytesWritten, 0, stringWritten, strlen(stringWritten), FS_WRITE_FLUSH) == 0);

    // Check file size
    SoftAssert(FSFILE_GetSize(fileHandle, &fileSize) == 0);
    // Verify file size
    SoftAssert(fileSize == bytesWritten);
    
    FSFILE_Close(fileHandle);
    FSUSER_DeleteFile(NULL, sdmcArchive, filePath);
    
    return true;
}

static bool TestSDMCDirCreateDelete(FS_archive sdmcArchive)
{
    Handle dirHandle;
    const static FS_path dirPath = FS_makePath(PATH_CHAR, "/test_dir_create_delete");
    
    // Create directory
    SoftAssert(FSUSER_CreateDirectory(NULL, sdmcArchive, dirPath) == 0);
    
    // Make sure the new dir exists
    SoftAssert(FSUSER_OpenDirectory(NULL, &dirHandle, sdmcArchive, dirPath) == 0);
    FSDIR_Close(dirHandle);
    
    SoftAssert(FSUSER_DeleteDirectory(NULL, sdmcArchive, dirPath) == 0);
    
    // Should fail to make sure the dir no longer exists
    SoftAssert(FSUSER_OpenDirectory(NULL, &dirHandle, sdmcArchive, dirPath) != 0);
    FSDIR_Close(dirHandle);
    
    return true;
}

static bool TestSDMCDirRename(FS_archive sdmcArchive)
{
    Handle dirHandle;
    const static FS_path dirPath = FS_makePath(PATH_CHAR, "/test_dir_rename");
    const static FS_path newDirPath = FS_makePath(PATH_CHAR, "/test_dir_rename_new");
    
    // Create dir
    FSUSER_CreateDirectory(NULL, sdmcArchive, dirPath);
    
    SoftAssert(FSUSER_RenameDirectory(NULL, sdmcArchive, dirPath, sdmcArchive, newDirPath) == 0);
    
    // Should fail to make sure the old dir no longer exists
    SoftAssert(FSUSER_OpenDirectory(NULL, &dirHandle, sdmcArchive, dirPath) != 0);
    FSDIR_Close(dirHandle);
    // Make sure the new dir exists
    SoftAssert(FSUSER_OpenDirectory(NULL, &dirHandle, sdmcArchive, newDirPath) == 0);
    FSDIR_Close(dirHandle);
    
    SoftAssert(FSUSER_DeleteDirectory(NULL, sdmcArchive, newDirPath) == 0);
    
    return true;
}

static void TestSDMC()
{
    FS_archive sdmcArchive = (FS_archive) { 0x00000009, { PATH_EMPTY, 1, (u8*) "" } };

    // Open SDMC
    TestResult("SDMC", "Opening archive", [&]{
        return FSUSER_OpenArchive(NULL, &sdmcArchive);
    });
    
    Test("SDMC", "Creating and deleting file", [&] {
        return TestSDMCFileCreateDelete(sdmcArchive);
    });
    
    Test("SDMC", "Renaming file", [&] {
        return TestSDMCFileRename(sdmcArchive);
    });
    
    Test("SDMC", "Writing to file", [&] {
        return TestSDMCFileWrite(sdmcArchive);
    });
    
    Test("SDMC", "Creating and deleting directory", [&] {
        return TestSDMCDirCreateDelete(sdmcArchive);
    });

    Test("SDMC", "Renaming directory", [&] {
        return TestSDMCDirRename(sdmcArchive);
    });

    // Close SDMC
    TestResult("SDMC", "Closing archive", [&]{
        return FSUSER_CloseArchive(NULL, &sdmcArchive);
    });
}


void TestAll()
{
    TestResult("FS", "Initializing service", [&]{
        return fsInit();
    });

    TestSDMC();

    TestResult("FS", "Exiting service", [&]{
        return fsExit();
    });
}

} // namespace
