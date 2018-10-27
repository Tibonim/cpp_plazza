#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		ComException : public CustomException {
  public:
    ComException(std::string const& message, std::string const& comment);
  };
}
