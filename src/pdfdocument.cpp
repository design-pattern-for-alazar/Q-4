#include "document/pdfdocument.h"

#ifdef HAS_PDF2HTML

PdfDocument::PdfDocument(fs::path path)
    : Document(path, new PdfParser, new DocumentStab), url(QUrl()) {}

const std::string PdfDocument::read() {
  fs::path path = getPath();
  std::string parsed = dynamic_cast<PdfParser*>(this->getParser())->parse(path);

  fs::path html_path = write(parsed);

  url = QUrl::fromLocalFile(html_path.c_str());

  return path;
}

#endif
