#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		SockException : public CustomException {
  public:
    SockException(std::string const& message, std::string const& comment);
  };
}
