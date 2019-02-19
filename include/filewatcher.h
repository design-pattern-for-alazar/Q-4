#ifndef FILEWATCHER_H_
#define FILEWATCHER_H_

#include <filesystem>
#include <mutex>
#include <vector>

#include <QThread>

#include "fileobserver.h"

namespace fs = std::filesystem;

class FileWatcher : public QThread {
 public:
  FileWatcher() = delete;
  FileWatcher(FileWatcher&) = delete;
  FileWatcher(FileWatcher&&) = delete;

  FileWatcher(const fs::path& p);

  FileWatcher& operator=(FileWatcher&) = delete;
  FileWatcher& operator=(FileWatcher&&) = delete;

  void setPath(const fs::path& p);

  void run();

  virtual void add(FileObserver*);
  virtual void remove(FileObserver*);
  virtual void notify();

  virtual void watch() = 0;  // implementation dependent

 protected:
  inline fs::path getPath() const { return file_path; }
  std::mutex mutex;

 private:
  std::vector<FileObserver*> observers;
  fs::path file_path;
};

#endif
