#include "documentfactory.h"

#include "factory/htmldocumentfactory.h"
#include "factory/manpagedocumentfactory.h"
#include "factory/markdowndocumentfactory.h"
#include "factory/pdfdocumentfactory.h"
#include "factory/textdocumentfactory.h"

DocumentFactory* DocumentFactory::_instance;

DocumentFactory* DocumentFactory::instance(std::string filename) {
  if (_instance != nullptr) delete _instance;

  if (_instance == nullptr) {
    std::regex ex(".*?\\.(?:txt|c|cpp|h|hpp|py|java)$", std::regex::icase);
    if (std::regex_search(filename, ex)) {
      _instance = new TextDocumentFactory();
    }
    else {
      ex = std::regex("(?:readme|.*?\\.(?:md|markdown))$", std::regex::icase);
      if (std::regex_search(filename, ex)) {
        _instance = new MarkDownDocumentFactory();
      }
      else {
        ex = std::regex(".*?\\.(?:xml|html|htm|json)$", std::regex::icase);
        if (std::regex_search(filename, ex)) {
          _instance = new HTMLDocumentFactory();
        }
#ifdef HAS_PDF2HTML
        ex = std::regex(".*?\\.pdf$", std::regex::icase);
        if (std::regex_search(filename, ex)) {
          _instance = new PdfDocumentFactory();
        }
#endif
#ifdef HAS_GROFF
        ex = std::regex(".*?\\.(1|2|3|4|5|6|7|8)$", std::regex::icase);
        if (std::regex_search(filename, ex)) {
          _instance = new ManPageDocumentFactory();
        }
#endif
      }
    }
  }

  return _instance;
}
