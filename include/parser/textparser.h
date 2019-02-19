#ifndef TEXTPARSER_H_
#define TEXTPARSER_H_

#include "parser.h"

class TextParser : public Parser {
 public:
  virtual std::string parse(const std::string& data) override;
};

#endif
