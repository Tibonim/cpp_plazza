#pragma once

#include <string>
#include "ICom.hpp"
#include "nonCopyable.hh"

namespace	utils {
  class		IParser : private nonCopyable {
  public:
    virtual void	parse(char token = ';') = 0;
    virtual std::string	const	&getString() const = 0;
    virtual void	setString(std::string const& str) = 0;
    virtual void	insert() = 0;
    virtual void	feedProtocol(com::ICom::SendProtocol& protocol) const = 0;
    virtual void	clearString(std::string& string) const = 0;
  };
}
