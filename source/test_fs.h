#ifndef TEST_FS_H
#define TEST_FS_H

void FS_TestAll();


void FS_TestInit();

void FS_TestSdmcOpen();
// FS_TestSdmcCreateFile();
void FS_TestSdmcRenameFile();
void FS_TestSdmcOpenFile();
void FS_TestSdmcOpenFileDirectly();
void FS_TestSdmcDeleteFile();
void FS_TestSdmcCreateDir();
// FS_TestSdmcRenameDir();
void FS_TestSdmcOpenDir();
// FS_TestSdmcDeleteDir();
// FS_TestSdmcDeleteDirRecursively();
void FS_TestSdmcClose();

#endif
