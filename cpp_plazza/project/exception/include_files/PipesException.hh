#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		PipesException : public CustomException {
  public:
    PipesException(std::string const& message, std::string const& comment);
  };
}
