#ifndef LINUXFILEWATCHER_H_
#define LINUXFILEWATCHER_H_

#include <filesystem>

#include "filewatcher.h"

#ifdef __linux__

class LinuxFileWatcher : public FileWatcher {
 public:
  LinuxFileWatcher() = delete;                   // no default constructer
  LinuxFileWatcher(LinuxFileWatcher&) = delete;  // no copy constructor
  LinuxFileWatcher(LinuxFileWatcher&&) = delete;

  LinuxFileWatcher(const fs::path& p);

  void watch() override;

 private:
  int fd;
  int wd;
};

#endif

#endif
