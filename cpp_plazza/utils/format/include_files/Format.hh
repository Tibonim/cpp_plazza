#pragma once

#include <fstream>
#include <streambuf>
#include <string>
#include <map>
#include "ParseInput.hh"
#include "FormatException.hh"
#include "nonCopyable.hh"

namespace utils {
  class Format : private utils::nonCopyable {
  public:
    Format(std::string const & = "confDic");
    std::string const &find(std::string const &) const;
  private:
    std::map<std::string, std::string>	_dictionary;
  };
}
