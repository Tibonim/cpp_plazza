#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		ipcException : public CustomException {
  public:
    ipcException(std::string const& comment, std::string const& message);
  };
}
