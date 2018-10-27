#pragma once

#include "ICom.hpp"

namespace	com {
  class		ACom : public ICom {
  public:
    ACom(std::size_t id);
    ~ACom() = default;
    virtual ICom	&operator<<(ICom::SendProtocol const &protocol) override;
    virtual ICom	&operator>>(ICom::SendProtocol& protocol) override;
    virtual void	sendCmd(ICom::SendProtocol const &protocol) = 0;
    virtual void	receivedCmd(ICom::SendProtocol& protocol) = 0;
    std::size_t	getId() const override;
    int			getFileDesc() const override;
  protected:
    std::size_t	_id;
    std::size_t	_input;
    std::size_t	_output;
    int		_fd;
    int		_fdW;
  };
}
