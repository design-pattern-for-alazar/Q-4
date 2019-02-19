#include "filewatcher/windowsfilewatcher.h"

#ifdef _WIN32
#include <stdlib.h>
#include <tchar.h>
#include <windows.h>
#include <limits>

WindowsFileWatcher::WindowsFileWatcher(fs::path p) : file_path(p) {}

long long writeTime(const fs::path& path) {
  struct _stat stFileInfo;
  if (_stat(fs::absolute(file_path).c_str(), &stFileInfo) > 0) {
    return stFileInfo.st_mtime;
  }
  return std::numeric_limits<long long>::max();
}

void WindowsFileWatcher::watch() {
  DWORD dwWaitStatus;
  HANDLE dwChangeHandle;
  TCHAR lpDrive[4];
  TCHAR lpFile[_MAX_FNAME];
  TCHAR lpExt[_MAX_EXT];
  lpDrive[2] = (TCHAR) '\\';
  lpDrive[3] = (TCHAR) '\0';

  long long mtime = writeTime(file_path);

  tsplitpath_s(fs::absolute(file_path).parent().c_str(), lpDrive, 4, NULL, 0,
               lpFile, _MAX_FNAME, lpExt, _MAX_EXT);

  dwChangeHandle = FindFirstChangeNotification(
      lpDir,                           // directory to watch
      TRUE,                            // do not watch subtree
      FILE_NOTIFY_CHANGE_LAST_WRITE);  // watch file name changes

  if (dwChangeHandles == INVALID_HANDLE_VALUE || dwChangeHandles == NULL) {
    fprintf(stderr, "ERROR: FindFirstChangeNotification function failed.\n");
    return;
  }

  while (TRUE) {
    dwWaitStatus = WaitForSingleObject(dwChangeHandle, INFINITE);
    switch (dwWaitStatus) {
      case WAIT_OBJECT_0:
        long long mtime_new = writeTime(file_path);

        if (mtime_new > mtime) { this->notify(); }

        break;
      case WAIT_TIMEOUT:
        break;
    }
  }
}
#endif
