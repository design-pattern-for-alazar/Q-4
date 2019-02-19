#include "parser/textparser.h"

std::string TextParser::parse(const std::string& data) {
  std::string parsedData = "<!Doctype html>\n<html><head></head><body><pre>";
  parsedData += data;
  parsedData += "</pre></body></html>";

  return parsedData;
}
