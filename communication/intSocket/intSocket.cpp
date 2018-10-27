#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <iostream>
#include <cstdio>
#include "SockException.hh"
#include "serialization.hh"
#include "intSocket.hh"

namespace com {

  intSocket::intSocket(std::size_t id, int input) : ACom{ id }
  {
    fd_set readfds;

    _socket = sizeof(addrOther);
    _input = input;
    if (_input < 999 || _input > 10000)
      throw plazza::SockException{ "Invalid Port", "intSocket" };
    if ((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
      throw plazza::SockException{ "Failed with socket", "intSocket" };

    addrMe.sin_family = AF_INET;
    addrMe.sin_port = htons(_input);
    addrMe.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(_socket, reinterpret_cast<struct sockaddr *>(&addrMe),
	     sizeof(addrMe)) == -1)
      throw plazza::SockException{ "Cannot bind", "intSocket" };

    addrOther.sin_family = AF_INET;
    addrOther.sin_addr.s_addr = htonl(INADDR_ANY);
    FD_ZERO(&readfds);
    FD_SET(_socket, &readfds);
  }

  intSocket::~intSocket()
  {
    shutdown(_socket, SHUT_RDWR);
  }

  void intSocket::sendCmd(ICom::SendProtocol const &protocol)
  {
    socklen_t		slen = sizeof(addrMe);
    socketProtocol	payload;
    Serialize		serial;

    if (inet_aton("127.0.0.1" , &addrMe.sin_addr) == 0)
      throw plazza::SockException{ "inet_aton() failed", "sendCmd" };
    payload.type = protocol.type;
    payload.remaining = 1;
    while (payload.remaining != 0){
      serial.SerializeCmd(protocol, payload);
      if (sendto(_socket, reinterpret_cast<const void *>(&payload),
		 sizeof(payload), 0,
		 reinterpret_cast<struct sockaddr *>(&addrMe), slen) == -1)
	return ;
    }
  }

  void intSocket::receivedCmd(ICom::SendProtocol& protocol)
  {
    socklen_t		slen = sizeof(addrOther);
    socketProtocol	payload;
    Serialize		serial;
    int			flags;

    protocol.fileName = "";
    protocol.information = "";
    payload.remaining = 1;
    if ((flags = fcntl(_socket, F_GETFL, 0)) == -1)
      flags = 0;
    fcntl(_socket, F_SETFL, flags | O_NONBLOCK);
    while (payload.remaining != 0){
      if (recvfrom(_socket, &payload, sizeof(payload),
		   0, reinterpret_cast<struct sockaddr *>(&addrOther), &slen) <= 0)
	return ;
      serial.SerializeCmd(payload, protocol);
      protocol.type = payload.type;
    }
  }

}
