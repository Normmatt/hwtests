#include "test_fs.h"

#include <3ds.h>

#include "test.h"

namespace FS {

static void TestSDMC()
{
    FS_archive sdmcArchive = (FS_archive) { 0x00000009, { PATH_EMPTY, 1, (u8*) "" } };
    
    FS_path dirPath = FS_makePath(PATH_CHAR, "/new_dir");
    Handle dirHandle;
    
    FS_path filePath = FS_makePath(PATH_CHAR, "/new_dir/new_file.txt");
    Handle fileHandle;
    u64 fileSize;
    
    // Post-dir-rename
    FS_path newDirPath = FS_makePath(PATH_CHAR, "/new_dir_renamed");
    // Post-both-rename
    FS_path newFilePath = FS_makePath(PATH_CHAR, "/new_dir_renamed/new_file_renamed.txt");
    
    u32 bytesWritten;

    // Open SDMC
    TestResult("SDMC", "Opening archive", [&]{
        return FSUSER_OpenArchive(NULL, &sdmcArchive);
    });

    // Create Directory
    TestResult("SDMC", "Creating directory", [&]{
        return FSUSER_CreateDirectory(NULL, sdmcArchive, dirPath);
    });

    // Open Directory
    TestResult("SDMC", "Opening directory handle", [&]{
        return FSUSER_OpenDirectory(NULL, &dirHandle, sdmcArchive, dirPath);
    });

    // Open File
    TestResult("SDMC", "Opening file handle", [&]{
        return FSUSER_OpenFile(NULL, &fileHandle, sdmcArchive, filePath, FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
    });

    // Write File
    TestResult("SDMC", "Writing data to file", [&]{
        const char* stringWritten = "A string\n";
        return FSFILE_Write(fileHandle, &bytesWritten, 0, stringWritten, strlen(stringWritten), FS_WRITE_FLUSH);
    });

    // Check File Size
    TestResult("SDMC", "Getting size of file", [&]{
        return FSFILE_GetSize(fileHandle, &fileSize);
    });

    // Verify File Size
    Test("SDMC", "Verifying size with written bytes", [&]{
        return fileSize == bytesWritten;
    });

    // Close File
    TestResult("SDMC", "Closing file handle", [&]{
        return FSFILE_Close(fileHandle);
    });

    // Close Directory
    TestResult("SDMC", "Closing directory handle", [&]{
        return FSDIR_Close(dirHandle);
    });
    
    // Rename Directory
    TestResult("SDMC", "Renaming directory", [&]{
        return FSUSER_RenameDirectory(NULL, sdmcArchive, dirPath, sdmcArchive, newDirPath);
    });
    
    // Rename File
    TestResult("SDMC", "Renaming file", [&]{
        // Post-dir-rename, pre-file-rename
        FS_path newDirFilePath = FS_makePath(PATH_CHAR, "/new_dir_renamed/new_file.txt");
        return FSUSER_RenameFile(NULL, sdmcArchive, newDirFilePath, sdmcArchive, newFilePath);
    });

    // Delete File
    TestResult("SDMC", "Deleting file", [&]{
        return FSUSER_DeleteFile(NULL, sdmcArchive, newFilePath);
    });    

    // Delete Directory
    TestResult("SDMC", "Deleting directory", [&]{
        return FSUSER_DeleteDirectory(NULL, sdmcArchive, newDirPath);
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
