#include <algorithm>
#include <cstdio>
#include <iterator>
#include <regex>

#include "algorithm.h"
#include "parser/markdownparser.h"

std::string& escape(std::string& s, bool all = false) {
  // escaped characters !"#$%&'()*+,-./:;<=>?@[]^_`{|}~
  replace(s, "\\!", "&#33;");
  replace(s, "\\\"", "&#34;");
  replace(s, "\\#", "&#35;");
  replace(s, "\\$", "$");
  replace(s, "\\%", "&#37;");
  replace(s, "\\&", "&#38;");
  replace(s, "\\'", "&#39;");
  replace(s, "\\(", "&#40;");
  replace(s, "\\)", "&#41;");
  replace(s, "\\*", "&#42;");
  replace(s, "\\+", "&#43;");
  replace(s, "\\,", "&#44;");
  replace(s, "\\-", "&#45");
  replace(s, "\\.", "&#46;");
  replace(s, "\\/", "&#47;");
  replace(s, "\\:", "&#58;");
  replace(s, "\\;", "&#59;");
  replace(s, "\\<", "&lt;");
  replace(s, "\\>", "&gt;");
  replace(s, "\\=", "=");
  replace(s, "\\?", "&#63;");
  replace(s, "\\@", "&#64;");
  replace(s, "\\[", "&#91;");
  replace(s, "\\]", "&#93;");
  replace(s, "\\^", "&#94;");
  replace(s, "\\_", "&#95;");
  replace(s, "\\`", "&#96;");
  replace(s, "\\{", "&#123;");
  replace(s, "\\|", "&#124;");
  replace(s, "\\}", "&#125;");
  replace(s, "\\~", "~");

  if (all) {
    replace(s, ">", "&gt");
    replace(s, "<", "&lt");
    replace(s, "*", "&#42;");
    replace(s, "_", "&#95;");
    replace(s, "-", "&#45");
    replace(s, "[", "&#91;");
    replace(s, "]", "&#93;");
    replace(s, "!", "&#33;");
    replace(s, "(", "&#40;");
    replace(s, ")", "&#41;");
  }

  return s;
}

std::string& escape(const std::string_view& s, bool all = false) {
  std::string str;
  std::copy(s.begin(), s.end(), std::back_inserter(str));

  return escape(str, all);
}

std::string MarkDownParser::parse(const std::string& data) {
  readLines(data);
  line = lines.cbegin();
  std::string html;

  while (line != lines.cend()) {
    html += parseLine(*line);
    ++line;
    if (line == lines.cbegin()) break;
  }

  return html;
}

void MarkDownParser::readLines(const std::string& data) {
  lines.clear();
  std::string_view current = data;
  size_t count = 0;

  for (auto i : data) {
    if (i == '\n') {
      lines.push_back(current.substr(0, count));
      current = current.substr(count + 1);
      count = 0;
      continue;
    }

    ++count;
  }

  lines.push_back(current);
}

void MarkDownParser::parseInlines(std::string& line) {
  parseInlineCode(line);
  parseBold(line);
  parseItalic(line);
  parseImage(line);
  parseLink(line);
}

std::string MarkDownParser::parseLine(std::string_view line) {
  std::string s = toString(line);
  parseHead(s) || parseList(s) || parseRule(s) || parseBlockQuote(s) ||
      parseCodeSpans(s) || parseFencedCode(s) || parseParagraph(s);

  parseInlines(s);
  return s;
}

bool MarkDownParser::parseParagraph(std::string& s, bool inContainer) {
  std::regex ex("^[ \t]*$");
  if (std::regex_search(s, ex)) {
    s += closing_tag;
    closing_tag = "";
  }
  else {
    if (inContainer) { s = "<p>" + s + "</p>"; }
    else if (closing_tag != "</p>") {
      s = "<p>" + escape(s);
      closing_tag = "</p>";
    }
    s += " ";
  }
  return true;
}

bool MarkDownParser::parseHead(std::string& s) {
  std::regex ex(
      "^[ \t]{0,3}(#{1,6})(?:(?:[ \t]+[ \t#]*)|(?:[ \t]+(.*[^ \t#])(.*)))?$");
  std::smatch m;

  if (std::regex_search(s, m, ex)) {
    std::string i = "6";
    i[0] = static_cast<char>(static_cast<unsigned>('0') + m[1].str().size());

    std::string element = m[2].str();
    // see if there is a #+ sticking with the string
    if (m[3].length() > 0) {
      std::string match = m[3].str();
      trim(match);
      std::string::size_type s = match.rfind(' ');
      if (s == std::string::npos) s = match.rfind('\t');

      if (s == std::string::npos)
        element += match;
      else
        element += match.substr(0, s);
    }

    s = closing_tag + "<h" + i + ">" + element + "</h" + i + ">";
    closing_tag = "";

    return true;
  }

  return false;
}

bool MarkDownParser::parseList(std::string& s) {
  return parseOrdered(s) || parseUnordered(s);
}

bool MarkDownParser::parseOrdered(std::string& s) {
  std::regex ex("^[ \t]{0,3}([0-9]+)([.\\)])(.*)");
  std::smatch m;

  if (std::regex_search(s, m, ex)) {
    std::string html = closing_tag;
    std::string start = m[2].str();
    std::string match = m[3].str();

    closing_tag = "";

    if (start == ")") { html += "<ol start=\"" + m[1].str() + "\"><li>"; }
    else {
      html += "<ol><li>";
    }

    parseHead(match) || parseRule(match) || parseParagraph(match, true);
    parseInlines(match);

    html += match + "</li>";
    ++line;

    while (line != lines.cend()) {
      s = toString(*line);

      if (std::regex_search(s, m, ex)) {
        if (m[2].str() != start) {
          // --line;
          html += "</ol>";
          s = html;
          return true;
        }
        match = m[3].str();
        parseHead(match) || parseRule(match);
        parseInlines(match);

        html += "<li>" + match + "</li>";
      }
      else {
        // --line;
        html += "</ol>";
        s = html;
        return true;
      }
      ++line;
    }

    html += "</ol>";
    s = html;
    return true;
  }

  return false;
}

bool MarkDownParser::parseUnordered(std::string& s) {
  std::regex ex("^[ \t]{0,3}(?:-|\\+|\\*)[ \t]*(.*)");
  std::smatch m;

  if (std::regex_search(s, m, ex)) {
    std::string html = closing_tag + "<ul><li>";
    std::string match = m[1].str();

    closing_tag = "";

    parseHead(match) || parseRule(match);
    parseInlines(match);

    html += match + "</li>";

    while (line != lines.cend()) {
      s = toString(*line);

      if (std::regex_search(s, m, ex)) {
        match = m[1].str();
        parseHead(match) ||
            parseRule(match);  // || parseParagraph(match, true);
        parseInlines(match);

        html += "<li>" + match + "</li>";
      }
      else {
        // --line;
        html += "</ul>";
        s = html;
        return true;
      }
      ++line;
    }

    html += "</ul>";
    s = html;
    return true;
  }

  return false;
}

bool MarkDownParser::parseRule(std::string& s) {
  // clang-format off
    std::regex ex(
        "^[ \t]{0,3}(?:(?:\\*[ \t]*){3,}|(?:-[ \t]*){3,}|(?:_[ \t]*){3,})[ \t]*$");
  // clang-format on

  if (std::regex_search(s, ex)) {
    s = closing_tag + "<hr />";
    closing_tag = "";
    return true;
  }

  return false;
}

bool MarkDownParser::parseCodeSpans(std::string& s) {
  std::regex ex("^[ \t]{4}(.*)");
  std::regex whitespace_only("^[ \t]+$");
  std::smatch m;

  if (std::regex_search(s, m, ex)) {
    std::string match = m[1].str();
    std::string html = "<pre><code>" + escape(match);
    std::string whitespaces;
    ++line;

    while (line != lines.cend()) {
      std::string line_str = toString(*line);

      if (std::regex_search(line_str, whitespace_only)) {
        whitespaces += line_str + '\n';
      }
      else if (std::regex_search(line_str, m, ex)) {
        match = m[1].str();
        html += whitespaces + escape(match);
        whitespaces = "";
      }
      else {
        html += "</pre></code>";
        s = html;
        // --line;
        return true;
      }
      ++line;
    }
    // if this reaches here we have finished parsing
    html = "</pre></code>";
    s = html;
    return true;
  }
  return false;
}

bool MarkDownParser::parseFencedCode(std::string& s) {
  // std::regex start("^[^ \t]{0,3}((`|~)\\2{2,})((?:(?!\\2).)*)(\\1?)(.*)");
  std::regex start("^[^ \t]{0,3}(`{3,}|~{3,})((?:(?!\\1).)*)$");
  std::regex end;
  std::smatch m;

  if (std::regex_search(s, m, start)) {
    // read lines until you get to the end
    std::string match = m[2].str();
    replace(match, "\"", "\\\"");

    if (m[1].str()[0] == '`') { end = std::regex("^[ \t]{0,3}`{3,}$"); }
    else {
      end = std::regex("^[ \t]{0,3}~{3,}$");
    }

    std::string html =
        closing_tag + "<pre><code class=\"language-" + match + "\">";

    closing_tag = "";
    ++line;

    while (line != lines.cend()) {
      std::string line_str = toString(*line);

      if (std::regex_search(line_str, end)) {
        html += "</code></pre>";
        s = html;
        //        --line;
        return true;
      }
      html += escape(line_str, true) + "\n";
      ++line;
    }
    html += "</code></pre>";
    s = html;
    return true;
  }

  return false;
}

bool MarkDownParser::parseBlockQuote(std::string& s) {
  //  size_t level = 1;
  std::regex ex("^[ \t]{0,3}(>+)[ \t]*(.*)");
  std::smatch m;

  if (std::regex_search(s, m, ex)) {
    std::string html = closing_tag + "<blockquote>";
    std::string match = m[2].str();

    parseHead(match) || parseRule(match) || parseParagraph(match);
    parseInlines(match);

    html += match;
    ++line;

    while (line != lines.cend()) {
      s = toString(*line);

      if (std::regex_search(s, m, ex)) {
        match = m[2].str();

        parseHead(match) || parseRule(match) || parseParagraph(match);
        parseInlines(match);

        html += match;
      }
      else {
        //        --line;
        html += "</blockquote>";
        s = html;
        return true;
      }
      ++line;
    }
    html += closing_tag + "</blockquote>";
    s = html;
  }
  return false;
}

void MarkDownParser::parseInlineCode(std::string& s) {
  std::regex ex("(`{3,}|~{3,})((?:(?!\\1).)*)\\1");
  std::smatch m;
  if (std::regex_search(s, m, ex)) {
    std::string match = m[2].str();
    escape(match, true);

    s = "<code>" + match + "</code>";
  }
}

void MarkDownParser::parseBold(std::string& s) {
  std::regex ex("(__|\\*\\*)(.*?)\\1");

  if (std::regex_search(s, ex)) { s = std::regex_replace(s, ex, "<b>$2</b>"); }
}

void MarkDownParser::parseItalic(std::string& s) {
  std::regex ex("(_|\\*)(.*?)\\1");

  if (std::regex_search(s, ex)) { s = std::regex_replace(s, ex, "<i>$2</i>"); }
}

void MarkDownParser::parseImage(std::string& s) {
  std::regex ex("!\\[(.*?)\\]\\((.*?)\\)");

  if (std::regex_search(s, ex)) {
    s = std::regex_replace(s, ex, "<img src='$2' alt='$1' />");
  }
}

void MarkDownParser::parseLink(std::string& s) {
  // this can be used  (?:\\[(.*)\\]\\((.*)\\))(?!\\!) but if images are
  // parsed first this isn't nessessary this increases overhead by using
  // negative lookup
  std::regex ex("\\[(.*?)\\]\\((.*?)\\)");

  if (std::regex_search(s, ex)) {
    s = std::regex_replace(s, ex, "<a href='$2'>$1</a>");
  }
}
