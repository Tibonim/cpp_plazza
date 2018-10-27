#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		barrierException : public CustomException {
  public:
    barrierException(std::string const& message, std::string const& comment);
  };
}
