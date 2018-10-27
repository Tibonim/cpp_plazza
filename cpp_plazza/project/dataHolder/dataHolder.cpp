#include <cstddef>
#include <fstream>
#include <utility>
#include <iostream>
#include "dataHolderException.hh"
#include "dataHolder.hh"

namespace	plazza {
  dataHolder::dataHolder(utils::Format const& format) : _format{ &format } {
    _parser = nullptr;
  }

  bool		dataHolder::lexeString(std::string const& str) const {
    if (_format->find(str) != "")
      return true;
    std::ifstream	ifs{ str };
    if (!ifs)
      return false;
    return true;
  }

  bool		dataHolder::isNull() const {
    return _parser == nullptr;
  }

  void		dataHolder::parseString(std::string const& str, char token) {
    if (isNull())
      throw dataHolderException{ "Parser is not set", "dataHolder" };
    _parser->setString(str);
    std::string	value{ "empty" };
    while (value != "") {
      _parser->parse(token);
      _parser->insert();
      value = _parser->getString();
      if (token == ';' && value != "")
	_stringList.push_back(value);
    }
  }

  bool		dataHolder::isEmpty() const {
    return _stringList.empty();
  }

  bool		dataHolder::insertInTree() {
    if (!_stringList.empty()) {
      parseString(_stringList.front(), ' ');
      _stringList.pop_front();
      return true;
    }
    return false;
  }

  void		dataHolder::feedProtocol(com::ICom::SendProtocol& protocol) const {
    _parser->feedProtocol(protocol);
  }

  void		dataHolder::setParser(dataHolder::parserPtr_t&& parser) {
    _parser = std::move(parser);
  }
}
