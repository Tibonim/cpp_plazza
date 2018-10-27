#include "timeException.hh"

namespace	plazza {
  timeException::timeException(std::string const& message, std::string const& comment)
    : CustomException{ message, comment } {}
}
