#pragma once

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ACom.hh"

namespace	com {
  class		intSocket : public ACom {
  public:
    intSocket(std::size_t id, int input);
    ~intSocket();
    void	sendCmd(ICom::SendProtocol const &protocol) override;
    void	receivedCmd(ICom::SendProtocol& protocol) override;
  private:
    int			_socket;
    struct sockaddr_in	addrMe;
    struct sockaddr_in	addrOther;
  };
}
