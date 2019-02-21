#ifndef PDFPARSER_H_
#define PDFPARSER_H_

#ifdef HAS_PDF2HTML

#include <filesystem>

#include "parser.h"

namespace fs = std::filesystem;

class PdfParser : public Parser {
 public:
  virtual std::string parse(const std::string& data);
  // overload pdftotext only uses path
  std::string parse(fs::path path);

  virtual ~PdfParser() {}
};

#endif

#endif
