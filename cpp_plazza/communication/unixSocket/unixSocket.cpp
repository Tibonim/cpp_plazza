#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <iostream>
#include "serialization.hh"
#include "unixSocket.hh"
#include "SockException.hh"

namespace com {

  unixSocket::unixSocket(std::size_t id, int input) : ACom{ id }
  {
    int flags;

    _socket = 0;
    _socketIn = 0;
    _input = input;
    _socketFileMe = ".s" + std::to_string(0) + "-"
      + std::to_string(input);

    if (_input < 999 || _input > 10000)
      throw plazza::SockException{"Invalid Port", "unixSocket"};
    if ((_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
      throw plazza::SockException{"Can't create socket", "unixSocket"};

    unlink(_socketFileMe.c_str());
    addrMe.sa_family = AF_UNIX;
    std::copy(_socketFileMe.begin(), _socketFileMe.end() + 1, addrMe.sa_data);
    _socketIn = socket(AF_UNIX, SOCK_STREAM, 0);
    if (bind(_socketIn, &addrMe, sizeof(struct sockaddr) + _socketFileMe.size()) == -1)
      throw plazza::SockException{"Failed to bind socket", "unixSocket"};
    if (-1 == (flags = fcntl(_socketIn, F_GETFL, 0)))
      flags = 0;
    fcntl(_socketIn, F_SETFL, flags | O_NONBLOCK);
    if (listen(_socketIn, 0) == -1){
      throw plazza::SockException{"Listen failed", "unixSocket"};
    }
  }

  unixSocket::~unixSocket()
  {
    unlink(_socketFileMe.c_str());
    shutdown(_socket, SHUT_RDWR);
  }

  void unixSocket::sendCmd(ICom::SendProtocol const &protocol)
  {
    socketProtocol	payload;
    Serialize		serial;
    int			flags;

    _socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == (flags = fcntl(_socket, F_GETFL, 0)))
      flags = 0;
    fcntl(_socket, F_SETFL, flags | O_NONBLOCK);
    if (connect(_socket, &addrMe,
		sizeof(struct sockaddr) + _socketFileMe.size()) == -1)
      return ;
    payload.type = protocol.type;
    payload.remaining = 1;
    while (payload.remaining != 0) {
      serial.SerializeCmd(protocol, payload);
      if (write(_socket, reinterpret_cast<const void *>(&payload),
		sizeof(payload)) == -1){
	throw plazza::SockException{"Can't write into socket", "unixSocket"};
      }
    }
    close(_socket);
  }

  void unixSocket::receivedCmd(ICom::SendProtocol& protocol)
  {
    socketProtocol	payload;
    Serialize		serial;
    int			dataSocket;
    int			flags;

    if ((dataSocket = accept4(_socketIn, NULL, NULL, O_NONBLOCK)) == -1)
      usleep(100);
    protocol.fileName = "";
    protocol.information = "";
    payload.remaining = 1;
    if (-1 == (flags = fcntl(dataSocket, F_GETFL, 0)))
      flags = 0;
    fcntl(dataSocket, F_SETFL, flags | O_NONBLOCK);
    while (payload.remaining != 0){
      if (read(dataSocket, &payload, sizeof(payload)) <= 0)
	return ;
      serial.SerializeCmd(payload, protocol);
      protocol.type = payload.type;
    }
  }

}
