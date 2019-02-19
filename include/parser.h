#ifndef PARSER_H_
#define PARSER_H_

#include <string>

class Parser {
 public:
  virtual std::string parse(const std::string& data) = 0;
  virtual ~Parser(){};
};

#endif
