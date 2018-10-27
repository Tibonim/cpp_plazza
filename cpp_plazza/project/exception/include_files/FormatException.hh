#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		FormatException : public CustomException {
  public:
    FormatException(std::string const& message, std::string const& comment);
  };
}
