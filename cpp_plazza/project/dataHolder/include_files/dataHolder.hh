#pragma once

#include <list>
#include <memory>
#include "nonCopyable.hh"
#include "Format.hh"
#include "IParser.hpp"

namespace	plazza {
  class		dataHolder : private utils::nonCopyable {
    typedef std::unique_ptr<utils::IParser>		parserPtr_t;
  public:
    dataHolder(utils::Format const& format);
    void		parseString(std::string const& str, char token = ';');
    void		setParser(parserPtr_t&& parser);
    void		feedProtocol(com::ICom::SendProtocol& protocol) const;
    bool		insertInTree();
    bool		isEmpty() const;
  private:
    bool		lexeString(std::string const& str) const;
    bool		isNull() const;
  private:
    parserPtr_t			_parser;
    utils::Format const		*_format;
    std::list<std::string>	_stringList;
  };
}
