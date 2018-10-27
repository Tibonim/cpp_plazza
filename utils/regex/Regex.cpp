#include "RegexException.hh"
#include "Regex.hh"

#include <iostream>

namespace utils {

  Regex::Regex(std::string const &regex, int flag) {
    if (regcomp(&_preg, regex.c_str(), flag) != 0)
      throw plazza::RegexException("Failed to compile regex '" + regex + "'",
				   "Regex::Regex()");
  }

  std::vector<std::string> const &Regex::getOccurences() const {
    return _occurences;
  }

  bool Regex::find(std::string const &input, int flag) {
    std::string tmpInput = input;
    regmatch_t rm[2];

    while (regexec(&_preg, tmpInput.c_str(), 2 , rm, flag) != REG_NOMATCH)
      {
	if (rm[1].rm_so < 0 ||
	    static_cast<unsigned>(rm[1].rm_so) > input.size() ||
	    rm[1].rm_eo < 0 ||
	    static_cast<unsigned>(rm[1].rm_eo) > input.size())
	  throw plazza::RegexException("Bad regex", "Regex::find()");
	_occurences.push_back(tmpInput.substr(rm[1].rm_so, rm[1].rm_eo - rm[1].rm_so));
	tmpInput = tmpInput.erase(0, rm[1].rm_eo);
      }
    return _occurences.size() != 0;
  }

  Regex::~Regex() {
    regfree(&_preg);
  }
}
