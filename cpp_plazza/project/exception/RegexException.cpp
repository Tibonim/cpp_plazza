#include "RegexException.hh"

namespace	plazza {
  RegexException::RegexException(std::string const& message,
			 std::string const& comment)
    : CustomException{ message, comment } {}
}
