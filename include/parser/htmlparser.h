#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include "parser.h"

class HTMLParser : public Parser {
 public:
  virtual std::string parse(const std::string& data) { return data; }
};

#endif
