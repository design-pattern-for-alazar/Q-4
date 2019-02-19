#include <algorithm>

#include "filewatcher.h"

FileWatcher::FileWatcher(const fs::path& p) { file_path = p; }

void FileWatcher::add(FileObserver* observer) {
  std::lock_guard<std::mutex> guard(mutex);
  observers.push_back(observer);
}

void FileWatcher::remove(FileObserver* observer) {
  std::lock_guard<std::mutex> guard(mutex);
  std::remove(observers.begin(), observers.end(), observer);
}

void FileWatcher::notify() {
  for (auto o : observers) o->update();
}

void FileWatcher::setPath(const fs::path& p) { file_path = p; }

void FileWatcher::run() { watch(); }
