#include "CondException.hh"

namespace	plazza {
  CondException::CondException(std::string const& message, std::string const& comment)
    : CustomException{ message, comment } {}
}
