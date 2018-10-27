#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		treeInfoException : public CustomException {
  public:
    treeInfoException(std::string const& message, std::string const& comment);
  };
}
