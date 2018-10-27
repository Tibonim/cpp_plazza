#pragma once

#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include "ACom.hh"

namespace	com {
  class		unixSocket : public ACom {
  public:
    unixSocket(std::size_t id, int input);
    ~unixSocket();
    void	sendCmd(ICom::SendProtocol const &protocol) override;
    void	receivedCmd(ICom::SendProtocol& protocol) override;
  private:
    int			_socket;
    int			_socketIn;
    struct sockaddr	addrMe;
    std::string		_socketFileMe;
  };
}
