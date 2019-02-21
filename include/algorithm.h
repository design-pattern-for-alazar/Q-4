#ifndef TRIM_H_
#define TRIM_H_

#include <algorithm>
#include <string>
#include <string_view>

std::string& trim(std::string& s) {
  size_t count = 0;

  for (auto c = s.end() - 1; c >= s.begin(); ++count, --c)
    if (*c != ' ' && *c != '\t') break;

  s = s.substr(0, s.size() - count);

  return s;
}

std::string& replace(std::string& s, const std::string& needle,
                     const std::string str) {
  std::string::size_type where;
  size_t needle_size = needle.size();

  while ((where = s.find(needle)) != std::string::npos) {
    s.replace(where, needle_size, str);
  }

  return s;
}

std::string& replace(std::string& s, char needle, const std::string& str) {
  std::string::size_type where;
  size_t needle_size = 1;

  while ((where = s.find(needle)) != std::string::npos) {
    s.replace(where, needle_size, str);
  }

  return s;
}

std::string& replace(std::string& s, char needle, char str) {
  for (auto c : s) {
    if (c == needle) { c = str; }
  }
  return s;
}

std::string toString(std::string_view line) {
  std::string s;
  //  line.remove_suffix(std::min(line.find_first_not_of(" "), line.size()));

  if (line.empty()) return s;

  std::copy(line.begin(), line.end(), std::back_inserter(s));

  return s;
}

bool startsWith(std::string str, std::string begining) {
  if (begining.size() > str.size()) return false;

  auto b = begining.begin();

  for (auto c = str.begin(); b < begining.end(); ++b, ++c)
    if (*b != *c) return false;

  return true;
}

bool endsWith(std::string str, std::string ending) {
  if (ending.size() > str.size()) return false;
  auto e = ending.rbegin();

  for (auto c = str.rbegin(); e < ending.rend(); ++e, ++c)
    if (*e != *c) return false;

  return true;
}

#endif
