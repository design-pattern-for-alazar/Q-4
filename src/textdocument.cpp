#include "document/textdocument.h"

TextDocument::TextDocument(fs::path path)
    : Document(path, new TextParser, new DocumentStab), url(QUrl()) {}

const std::string TextDocument::read() {
  std::string data = Document::read();
  std::string parsed = getParser()->parse(data);

  fs::path html_path = write(parsed);

  url = QUrl::fromLocalFile(html_path.c_str());

  return data;
}
