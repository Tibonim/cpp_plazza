#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		timeException : public CustomException {
  public:
    timeException(std::string const& message, std::string const& comment);
  };
}
