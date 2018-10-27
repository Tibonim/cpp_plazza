#include "SockException.hh"

namespace	plazza {
  SockException::SockException(std::string const& message, std::string const& comment)
    : CustomException{ message, comment } {}
}
