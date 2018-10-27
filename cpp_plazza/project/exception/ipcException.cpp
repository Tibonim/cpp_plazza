#include "ipcException.hh"

namespace	plazza {
  ipcException::ipcException(std::string const& comment,
			     std::string const& message)
    : CustomException{ comment, message } {}
}
