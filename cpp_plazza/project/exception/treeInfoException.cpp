#include "treeInfoException.hh"

namespace	plazza {
  treeInfoException::treeInfoException(std::string const& message,
				       std::string const& comment)
    : CustomException{ message, comment } {}
}
