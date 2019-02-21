#ifndef PDFDOCUMENTFACTORY_H_
#define PDFDOCUMENTFACTORY_H_

#ifdef HAS_PDF2HTML

#include "document/pdfdocument.h"
#include "documentfactory.h"
#include "parser/pdfparser.h"

class PdfDocumentFactory : public DocumentFactory {
 public:
  Document* createDocument(fs::path path) { return new PdfDocument(path); }
};

#endif

#endif
