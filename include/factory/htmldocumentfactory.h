#ifndef HTMLDOCUMENTFACTORY_H_
#define HTMLDOCUMENTFACTORY_H_

#include "document/htmldocument.h"
#include "documentfactory.h"
#include "parser/htmlparser.h"

class HTMLDocumentFactory : public DocumentFactory {
 public:
  Document* createDocument(fs::path path) { return new HTMLDocument(path); }
};

#endif
