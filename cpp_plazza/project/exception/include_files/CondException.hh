#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		CondException : public CustomException {
  public:
    CondException(std::string const& message, std::string const& comment);
  };
}
