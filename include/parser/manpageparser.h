#ifndef MANPAGEPARSER_H_
#define MANPAGEPARSER_H_

#include <list>
#include <string>
#include <string_view>

#include "parser.h"

#ifdef HAS_GROFF

class ManPageParser : public Parser {
 public:
  virtual std::string parse(const std::string& data) override;

  // protected:
  // void readLines(const std::string& data);

  // bool parseTitle(std::string& data);
  // bool parseSection(std::string& data);
  // bool parseParagraph(std::string& data);
  // bool parseBoldBlock(std::string& data);
  // bool parseItalicBlock(std::string& data);

  // void parseBold(std::string& data);
  // void parseItalic(std::string& data);
  // void parseLineBreak(std::string& data);
  // void parseCenterLine(std::string& data);

  // void parseControlChar(std::string& data);

  // private:
  // std::list<std::string_view> lines;
  // std::list<std::string_view>::const_iterator line;

  // char controlchar;
};

#endif

#endif
