#ifndef TEXTDOCUMENTFACTORY_H_
#define TEXTDOCUMENTFACTORY_H_

#include "document/textdocument.h"
#include "documentfactory.h"
#include "parser/textparser.h"

class TextDocumentFactory : public DocumentFactory {
 public:
  Document* createDocument(fs::path path) { return new TextDocument(path); }
};

#endif
