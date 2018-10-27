#include "dataHolderException.hh"

namespace	plazza {
  dataHolderException::dataHolderException(std::string const& message,
					   std::string const& comment)
    : CustomException{ message, comment } {}
}
