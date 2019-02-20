//#include <algorithm>
//#include <cstdio>
//#include <iterator>
//#include <regex>

//#include "algorithm.h"
#include "parser/manpageparser.h"

#ifdef HAS_GROFF

#include <QProcess>
#include <QStringList>

std::string ManPageParser::parse(const std::string& data) {
  QProcess groff;
  groff.start("groff", QStringList() << "-Thtml"
                                     << "-man");
  if (!groff.waitForStarted()) return "";

  groff.write(data.c_str());
  groff.closeWriteChannel();

  if (!groff.waitForFinished()) return "";

  return groff.readAll().data();
}

#endif

// std::string escape(std::string& s) {
// replace(s, "\\\"", "&#34;");
// replace(s, "\\%", "&#37;");
// replace(s, "\\'", "&#39;");
// replace(s, "\\-", "&#45");
// replace(s, "\\.", "&#46;");
// replace(s, "\\`", "&#96;");
// replace(s, "<", "&gt");
// replace(s, "<", "&lt");
//}

// std::string ManPageParser::parse(const std::string& data) { readLines(data);
// }

// void ManPageParser::readLines(const std::string& data) {
// std::string_view current = data;
// size_t count = 0;

// for (auto i : data) {
// if (i == '\n') {
// lines.push_back(current.substr(0, count);
// current = current.substr(count+1);
// count = 0;
// continue;
//}

//++count;
//}

// lines.push_back(current);
//}

// std::string ManPageParser::parseLine(std::string_view line) {
// std::string s = toString(line);
//}

// bool ManPageParser::parseTitle(std::string& s) {
// std::regex ex("^\\.TH (.*?) .*");
// std::smatch m;
// if (std::regex_search(s, m, ex)) { return true; }

// return false;
//}

// bool ManPageParser::parseSection(std::string& s) {
// std::regex ex("^\\.SH (.*)");
// std::smatch m;

// if (std::regex_search(s, m, ex)) {
// s = std::regex_replace(s, ex, "<h2 class=\"troffsh\">$2</h2>");
// return true;
//}

// return false;
//}

// bool ManPageParser::parseParagraph(std::string& s) { return true; }

// bool ManPageParser::parseBoldBlock(std::string& s) {
// std::regex ex("^\\.B[IR]? (*)");  // know if it is regular or italics
// std::smatch m;

// if (std::regex_search(s, m, ex)) {
// if (m[1].str() == "") {
//++line;
// s = "<b>" + *line + "</b>";
//}
// else {
// s = "<b>" + m[1].str() + "</b>";
//}
// return true;
//}
// return false;
//}

// bool ManPageParser::parseItalicsBlock(std::string& s) {
// std::regex ex("^\\.I[BR]? (*)");  // know if it is regular or italics
// std::smatch m;

// if (std::regex_search(s, m, ex)) {
// if (m[1].str() == "") {
//++line;
// s = "<i>" + *line + "</i>";
//}
// else {
// s = "<i>" + m[1].str() + "</i>";
//}
// return true;
//}
// return false;
//}

// void ManPageParser::parseBold(std::string& s) {
// std::regex ex("\\fB(.*?)\\fR");
// std::smatch m;

// if (std::regex_search(s, m, ex)) { s = "<b>" + m[1].str() + "</b>"; }
//}

// void ManPageParser::parseItalic(std::string& s) {
// std::regex ex("\\fI(.*?)\\fR");
// std::smatch m;

// if (std::regex_search(s, m, ex)) { s = "<i>" + m[1].str() + "</i>"; }
//}

// void ManPageParser::parseLineBreak(std::string& s) {
// if (startsWith(s, ".br")) { s = "<br />"; }
//}
