#pragma once

#include <sys/types.h>
#include <regex.h>
#include <string>
#include <vector>
#include "RegexException.hh"

namespace utils {

  class Regex {
  public:
    Regex(std::string const &, int = REG_EXTENDED);
    ~Regex();

    bool	find(std::string const &, int = 0);
    std::vector<std::string> const &getOccurences() const;
  private:
    regex_t	_preg;
    std::vector<std::string> _occurences;
    unsigned	_countOccurences(std::string const &, int);
  };
}
