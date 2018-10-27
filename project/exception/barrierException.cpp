#include "barrierException.hh"

namespace	plazza {
  barrierException::barrierException(std::string const& message,
				     std::string const& comment)
    : CustomException{ message, comment } {}
}
