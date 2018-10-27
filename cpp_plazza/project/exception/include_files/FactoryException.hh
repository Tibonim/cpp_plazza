#pragma once

#include "CustomException.hh"

namespace	plazza {
  class		FactoryException : public CustomException {
  public:
    FactoryException(std::string const& message,
		     std::string const& comment);
  };
}
