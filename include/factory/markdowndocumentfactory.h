#ifndef MARKDOWNDOCUMENTFACTORY_H_
#define MARKDOWNDOCUMENTFACTORY_H_

#include "document/markdowndocument.h"
#include "documentfactory.h"
#include "parser/markdownparser.h"

class MarkDownDocumentFactory : public DocumentFactory {
 public:
  Document* createDocument(fs::path path) { return new MarkDownDocument(path); }
};

#endif
