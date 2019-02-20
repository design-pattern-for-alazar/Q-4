#ifndef TEXTDOCUMENT_H_
#define TEXTDOCUMENT_H_

#include <filesystem>
#include <stdexcept>

#include <QFile>

#include "document.h"
#include "parser/textparser.h"

namespace fs = std::filesystem;

class TextDocument : public Document {
 public:
  TextDocument(fs::path path);
  virtual const QUrl convertToHTML() override { return url; }
  virtual const std::string read() override;

 private:
  QUrl url;
};

#endif
