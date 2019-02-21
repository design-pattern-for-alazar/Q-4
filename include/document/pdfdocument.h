#ifndef PDFDOCUMENT_H_
#define PDFDOCUMENT_H_

#ifdef HAS_PDF2HTML
#include <filesystem>

#include <QUrl>

#include "document.h"
#include "parser/pdfparser.h"

namespace fs = std::filesystem;

class PdfDocument : public Document {
 public:
  PdfDocument(fs::path path);
  virtual const QUrl convertToHTML() override { return url; }
  virtual const std::string read() override;

 private:
  QUrl url;
};

#endif

#endif
