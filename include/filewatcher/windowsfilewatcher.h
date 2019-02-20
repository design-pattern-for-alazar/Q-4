#ifndef WINDOWSFILEWATCHER_H_
#define WINDOWSFILEWATCHER_H_

#include <filesystem>
#include <thread>

#include "filewatcher.h"

#ifdef _WIN32
namespace fs = std::filesystem;

class WindowsFileWatcher : public FileWatcher {
 public:
  WindowsFileWatcher() = delete;                     // no default constructer
  WindowsFileWatcher(WindowsFileWatcher&) = delete;  // no copy constructor

  WindowsFileWatcher(const fs::path& p) { file_path = p; }

  void watch();

 private:
  fs::path file_path;
};

#endif

#endif
