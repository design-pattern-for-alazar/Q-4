#include "document/htmldocument.h"

HTMLDocument::HTMLDocument(fs::path path)
    : Document(path, new HTMLParser, new DocumentStab) {
  url = QUrl::fromLocalFile(path.c_str());
}

const std::string HTMLDocument::read() { return ""; }
