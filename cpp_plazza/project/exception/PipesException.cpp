#include "PipesException.hh"

namespace	plazza {
  PipesException::PipesException(std::string const& message, std::string const& comment)
    : CustomException{ message, comment } {}
}
