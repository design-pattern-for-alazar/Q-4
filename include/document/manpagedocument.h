#ifndef MANPAGEDOCUMENT_H_
#define MANPAGEDOCUMENT_H_

#include "document.h"
#include "parser/manpageparser.h"

#ifdef HAS_GROFF

class ManPageDocument : public Document {
 public:
  ManPageDocument(fs::path path);
  virtual const QUrl convertToHTML() override { return url; }
  virtual const std::string read() override;

 private:
  QUrl url;
};

#endif

#endif
