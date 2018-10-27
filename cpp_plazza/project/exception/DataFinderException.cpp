#include "DataFinderException.hh"

namespace	plazza {
  DataFinderException::DataFinderException(std::string const& message,
			 std::string const& comment)
    : CustomException{ message, comment } {}
}
