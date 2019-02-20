#ifndef MARKDOWNPARSER_H_
#define MARKDOWNPARSER_H_

#include <list>
#include <string>
#include <string_view>

#include "parser.h"

class MarkDownParser : public Parser {
 public:
  virtual std::string parse(const std::string& data) override;

 protected:
  // general functions
  void readLines(const std::string& data);

  inline void parseInlines(std::string& line);

  std::string parseLine(std::string_view line);

  // block elements
  bool parseParagraph(std::string& s, bool inContainer = false);

  bool parseHead(std::string& s);

  bool parseList(std::string& s);

  bool parseOrdered(std::string& s);

  bool parseUnordered(std::string& s);

  bool parseRule(std::string& s);

  bool parseCodeSpans(std::string& s);

  bool parseFencedCode(std::string& s);

  bool parseBlockQuote(std::string& s);

  // inline elements
  inline void parseInlineCode(std::string& s);

  inline void parseBold(std::string& s);

  inline void parseItalic(std::string& s);

  inline void parseImage(std::string& s);

  inline void parseLink(std::string& s);

 private:
  std::string closing_tag;

  std::list<std::string_view> lines;
  std::list<std::string_view>::const_iterator line;
};

#endif
