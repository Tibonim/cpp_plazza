#include "ComException.hh"

namespace	plazza {
  ComException::ComException(std::string const& message, std::string const& comment)
    : CustomException{ message, comment } {}
}
