#include "ForkException.hh"

namespace	plazza {
  ForkException::ForkException(std::string const& message, std::string const& comment)
    : CustomException{ message, comment } {}
}
