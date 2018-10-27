#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "serialization.hh"
#include "PipesException.hh"
#include "ICom.hpp"
#include "fifoPipes.hh"

namespace	com {
  NamedPipe::NamedPipe(std::size_t id, int input) : ACom{ id }{
    _input = input;
    _fifoFileMe = ".f" + std::to_string(0) + "-"
      + std::to_string(input);
    unlink(_fifoFileMe.c_str());
    if (_input < 999 || _input > 10000)
      throw plazza::PipesException{"Invalid input", "fifoPipes"};
    if (mkfifo(_fifoFileMe.c_str(), 0666) == -1)
      throw plazza::PipesException{"Can't create fifo file", "fifoPipes"};
    if ((_fd = open(_fifoFileMe.c_str(), O_RDONLY | O_NONBLOCK)) == -1)
      throw plazza::PipesException{"Can't open fifo file", "ReceivedCmd"};
    _fdW = open(_fifoFileMe.c_str(), O_WRONLY);
    if (_fdW == -1)
      throw plazza::PipesException{"Can't open fifo file", "sendCmd"};
  }

  NamedPipe::~NamedPipe() {
    unlink(_fifoFileMe.c_str());
    close(_fd);
    close(_fdW);
  }

  void		NamedPipe::sendCmd(ICom::SendProtocol const &protocol) {
    ICom::socketProtocol	proto;
    Serialize			serial;

    proto.type = protocol.type;
    proto.remaining = 1;
    while (proto.remaining != 0) {
      serial.SerializeCmd(protocol, proto);
      if (write(_fdW, &proto, sizeof(proto)) == -1)
	throw plazza::PipesException{"Failed to write into fifo file",
	    "fifoPipes"};
    }
  }

  void		NamedPipe::receivedCmd(ICom::SendProtocol& protocol) {
    ICom::socketProtocol	proto;
    Serialize			serial;

    protocol.fileName = "";
    protocol.information = "";
    proto.remaining = 1;
    while (proto.remaining != 0) {
      if (read(_fd, &proto, sizeof(proto)) > 0) {
	serial.SerializeCmd(proto, protocol);
	protocol.type = proto.type;
      }
      else
	proto.remaining = 0;
    }
  }
}
