#include <sstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "ParseInput.hh"

namespace	utils {
  void	ParseInput::parse(char token) {
    _first = _last;
    for (; _last != _str.end(); ++_last) {
      if ((*_last) == token) {
	_parse = std::string(_first, _last);
	clearString(_parse);
	clearIterator(token);
	return ;
      }
    }
    _parse = std::string(_first, _last);
    clearString(_parse);
    clearIterator(token);
  }

  void	ParseInput::clearString(std::string& str) const {
    std::istringstream	iss{ str };
    std::string		tmp;
    std::string		res;

    if (iss >> tmp)
      res += tmp;
    while (iss >> tmp)
      res += ' ' + tmp;
    str = res;
  }

  void	ParseInput::clearIterator(char token) {
    for (; (*_last) == token && _last != _str.end(); ++_last);
  }

  void	ParseInput::setString(std::string const& str) {
    _str = str;
    _first = _str.begin();
    _last = _str.begin();
  }

  std::string const	&ParseInput::getString() const {
    return _parse;
  }

  void			ParseInput::insert() {
    return ;
  }

  void			ParseInput::feedProtocol(com::ICom::SendProtocol&) const {
    return ;
  }
}
