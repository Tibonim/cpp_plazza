#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		dataHolderException : public CustomException {
  public:
    dataHolderException(std::string const& message, std::string const& comment);
  };
}
