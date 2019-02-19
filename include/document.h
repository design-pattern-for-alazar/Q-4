#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <QUrl>
#include <filesystem>

#include "fileobserver.h"
#include "parser.h"

#include "../documentstab.h"

namespace fs = std::filesystem;

class Document : public FileObserver {
 public:
  Document(fs::path path, Parser* parser, DocumentStab* s);
  virtual ~Document();
  virtual const QUrl convertToHTML() = 0;
  virtual const std::string read();
  const fs::path write(const std::string& data);

  const fs::path getPath();
  const DocumentStab* getStab();

  void update();

 protected:
  Parser* getParser();

 private:
  fs::path filepath;
  Parser* parser;
  DocumentStab* s;

  //  static Document* document;
};

#endif
