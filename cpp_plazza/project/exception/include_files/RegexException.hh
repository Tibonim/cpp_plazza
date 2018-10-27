#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		RegexException : public CustomException {
  public:
    RegexException(std::string const& message, std::string const& comment);
  };
}
