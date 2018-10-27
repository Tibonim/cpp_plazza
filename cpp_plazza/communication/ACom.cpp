#include "ACom.hh"

namespace	com {
  ACom::ACom(std::size_t id) : _id{ id } {}

  std::size_t	ACom::getId() const {
    return _id;
  }

  int		ACom::getFileDesc() const {
    return _fd;
  }

  ICom		&ACom::operator<<(ICom::SendProtocol const &protocol) {
    sendCmd(protocol);
    return *this;
  }

  ICom		&ACom::operator>>(ICom::SendProtocol& protocol) {
    receivedCmd(protocol);
    return *this;
  }

}
