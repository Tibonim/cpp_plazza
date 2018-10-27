#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		DataFinderException : public CustomException {
  public:
    DataFinderException(std::string const& message, std::string const& comment);
  };
}
