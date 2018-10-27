#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		ForkException : public CustomException {
  public:
    ForkException(std::string const& message, std::string const& comment);
  };
}
