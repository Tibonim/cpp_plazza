#include "FormatException.hh"

namespace	plazza {
  FormatException::FormatException(std::string const& message,
			 std::string const& comment)
    : CustomException{ message, comment } {}
}
