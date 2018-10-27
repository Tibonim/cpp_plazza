#include "FactoryException.hh"

namespace	plazza {
  FactoryException::FactoryException(std::string const& message,
				     std::string const& comment)
    : CustomException{ message, comment } {}
}
