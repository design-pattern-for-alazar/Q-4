#include "document/markdowndocument.h"

MarkDownDocument::MarkDownDocument(fs::path path)
    : Document(path, new MarkDownParser, new DocumentStab), url(QUrl()) {}

const std::string MarkDownDocument::read() {
  std::string data = Document::read();
  std::string parsed = this->getParser()->parse(data);

  fs::path html_path = write(parsed);

  url = QUrl::fromLocalFile(html_path.c_str());

  return data;
}
