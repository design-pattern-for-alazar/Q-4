#ifndef MARKDOWNDOCUMENT_H_
#define MARKDOWNDOCUMENT_H_

#include <filesystem>
#include <stdexcept>

#include <QFile>

#include "document.h"
#include "parser/markdownparser.h"

namespace fs = std::filesystem;

class MarkDownDocument : public Document {
 public:
  MarkDownDocument(fs::path path);
  virtual const QUrl convertToHTML() override { return url; }
  const std::string read() override;

 private:
  QUrl url;
};

#endif
