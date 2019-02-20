#ifndef HTMLDOCUMENT_H_
#define HTMLDOCUMENT_H_

#include <filesystem>
#include <stdexcept>

#include "document.h"
#include "parser/htmlparser.h"

namespace fs = std::filesystem;

// this is a stub not used by the application
class HTMLDocument : public Document {
 public:
  // HTMLDocument(fs::path path, HTMLParser parser);
  HTMLDocument(fs::path path);

  virtual const QUrl convertToHTML() override { return url; }
  virtual const std::string read() override;

 private:
  QUrl url;
};

#endif
