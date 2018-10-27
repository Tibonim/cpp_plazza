#pragma once

#include "ACom.hh"

namespace	com {
  class		NamedPipe : public ACom {
  public:
    NamedPipe(std::size_t id, int input);
    ~NamedPipe();
    void	sendCmd(ICom::SendProtocol const &protocol) override;
    void	receivedCmd(ICom::SendProtocol& protocol) override;
  private:
    std::string	_fifoFileMe;
    std::string	_fifoFileOther;
  };
}
