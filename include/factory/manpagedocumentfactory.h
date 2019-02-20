#ifndef MANPAGEDOCUMENTFACTORY_H_
#define MANPAGEDOCUMENTFACTORY_H_

#ifdef HAS_GROFF
#include "document/manpagedocument.h"
#include "documentfactory.h"
#include "parser/manpageparser.h"

class ManPageDocumentFactory : public DocumentFactory {
 public:
  Document* createDocument(fs::path path) { return new ManPageDocument(path); }
};

#endif

#endif
