#ifndef DOCUMENTFACTORY_H_
#define DOCUMENTFACTORY_H_

#include <regex>

#include "filewatcher/bsdfilewatcher.h"
#include "filewatcher/linuxfilewatcher.h"
#include "filewatcher/windowsfilewatcher.h"

#include "document.h"
#include "filewatcher.h"
#include "parser.h"

class DocumentFactory {
 public:
  static DocumentFactory* instance(std::string filename);

  virtual ~DocumentFactory() {}

  virtual Document* createDocument(const fs::path path) = 0;

  FileWatcher* createFileWatcher(const fs::path path) {
    FileWatcher* watcher;
#if defined(__APPLE_CC__) || defined(BSD)
    watcher = new BSDFileWatcher(path);
#elif defined(__linux__)
    watcher = new LinuxFileWatcher(path);
#else
    watcher = new WindowsFileWatcher(path);
#endif
    return watcher;
  }

 protected:
  DocumentFactory() { _instance = nullptr; }

 private:
  static DocumentFactory* _instance;
};

#endif
