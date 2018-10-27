#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		KeyFinderException : public CustomException {
  public:
    KeyFinderException(std::string const& message, std::string const& comment);
  };
}
