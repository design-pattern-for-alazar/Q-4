#include <fstream>
#include <iostream>
#include <string>
#include <system_error>

#include <QDebug>

#include "document.h"

#ifdef _WIN32
inline int access(const char* path, int mode) { return _access(path, mode); }
#else
#include <unistd.h>
#endif

bool hasReadPermissions(fs::path& path) {
  return access(path.c_str(), R_OK) >= 0;
}

Document::Document(fs::path path, Parser* parser, DocumentStab* s) {
  if (fs::exists(path)) {
    if (fs::is_regular_file(path)) {
      if (hasReadPermissions(path)) {
        filepath = path;
        this->parser = parser;
        this->s = s;
      }
      else {
        throw fs::filesystem_error(
            std::string("You don't have read access permmission to the file ") +
                fs::absolute(path).c_str() + ".",
            fs::absolute(path),
            std::make_error_code(std::errc::permission_denied));
      }
    }
    else {
      throw fs::filesystem_error(
          std::string("The file ") + fs::absolute(path).c_str() +
              " isn't a regular file.",
          fs::absolute(path), std::make_error_code(std::errc::is_a_directory));
    }
  }
  else {
    throw fs::filesystem_error(
        std::string("The file ") + fs::absolute(path).c_str() +
            " doesn't exist.",
        fs::absolute(path),
        std::make_error_code(std::errc::no_such_file_or_directory));
  }
}

Document::~Document() {
  delete parser;
  delete s;
}

const std::string Document::read() {
  std::ifstream in(filepath, std::ios::in);

  if (in.is_open()) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(static_cast<unsigned>(in.tellg()));
    in.seekg(0, std::ios::beg);

    in.read(&contents[0], static_cast<long>(contents.size()));
    in.close();
    return contents;
  }

  throw fs::filesystem_error(
      std::string("Can't read file ") + fs::absolute(filepath).c_str(),
      fs::absolute(filepath),
      std::make_error_code(std::errc::bad_file_descriptor));
}

const fs::path Document::write(const std::string& data) {
  fs::path tempdir = fs::temp_directory_path().append("dpdocviewer");
  fs::create_directories(tempdir);
  std::hash<std::string> hash_fn;
  auto hash = hash_fn(fs::absolute(filepath).string());

  fs::path write_to = tempdir.append(std::to_string(hash) + ".html");

  std::ofstream of(write_to, std::ios::out | std::ios::trunc);

  if (of.is_open()) {
    of.write(data.c_str(), static_cast<std::streamsize>(data.size()));
    of.close();
    return write_to;
  }

  throw fs::filesystem_error(
      std::string("Can't open file ") + fs::absolute(filepath).c_str() +
          " for writing.",
      fs::absolute(filepath),
      std::make_error_code(std::errc::bad_file_descriptor));
}

const fs::path Document::getPath() { return filepath; }

const DocumentStab* Document::getStab() { return s; }

void Document::update() {
  read();
  s->update();
}

Parser* Document::getParser() { return parser; }
