#ifndef BSDFILEWATCHER_H_
#define BSDFILEWATCHER_H_

#include <filesystem>
#include <thread>

#include "filewatcher.h"

#if defined(__APPLE_CC__) || defined(BSD)
class BSDFileWatcher : public FileWatcher {
 public:
  BSDFileWatcher() = delete;                 // no default constructer
  BSDFileWatcher(BSDFileWatcher&) = delete;  // no copy constructor

  BSDFileWatcher(const fs::path& p) { file_path = p; }

  void watch();

 private:
  fs::path file_path;
};
#endif

#endif
