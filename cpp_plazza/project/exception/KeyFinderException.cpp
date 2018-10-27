#include "KeyFinderException.hh"

namespace	plazza {
  KeyFinderException::KeyFinderException(std::string const& message,
			 std::string const& comment)
    : CustomException{ message, comment } {}
}
