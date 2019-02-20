#include "document/manpagedocument.h"
#ifdef HAS_GROFF
ManPageDocument::ManPageDocument(fs::path path)
    : Document(path, new ManPageParser, new DocumentStab), url(QUrl()) {}

const std::string ManPageDocument::read() {
  std::string data = Document::read();
  std::string parsed = this->getParser()->parse(data);

  fs::path html_path = write(parsed);

  url = QUrl::fromLocalFile(html_path.c_str());

  return data;
}
#endif
