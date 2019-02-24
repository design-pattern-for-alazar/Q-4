#include "parser/pdfparser.h"

#ifdef HAS_PDF2HTML
#include <filesystem>

#include <QProcess>
#include <QStringLiteral>

std::string PdfParser::parse(const std::string&) { return ""; }

std::string PdfParser::parse(fs::path path) {
  QProcess pdftotext;
  pdftotext.start("pdftohtml", QStringList() << "-q"
                                             << "-p"
                                             << "-stdout"
                                             << "-i" << path.c_str());
  if (!pdftotext.waitForStarted()) return "";

  //  pdftotext.closeWriteChannel();

  if (!pdftotext.waitForFinished()) return "";

  return pdftotext.readAll().data();
}

#endif
