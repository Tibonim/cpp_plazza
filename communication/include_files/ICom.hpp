#pragma once

#include <string>

#define MAX_MSG (250)

namespace	com {
  class		ICom {
  public:
    enum		Status {
      AVAILABLE,
      BUSY,
      CLOSED,
      FINISH
    };
#pragma pack (push, 1)
    struct	socketProtocol {
      int		remaining;
      Status		type;
      uint8_t		fileName[MAX_MSG + 1];
      uint8_t		information[MAX_MSG + 1];
    };
#pragma pack (pop)
    struct	SendProtocol {
      Status		type;
      std::string	fileName;
      std::string	information;
    };
    virtual ~ICom() = default;
    virtual ICom	&operator<<(ICom::SendProtocol const & protocol) = 0;
    virtual ICom	&operator>>(ICom::SendProtocol& protocol) = 0;
    virtual void	sendCmd(ICom::SendProtocol const &protocol) = 0;
    virtual void	receivedCmd(ICom::SendProtocol& protocol) = 0;
    virtual std::size_t	getId() const = 0;
    virtual int		getFileDesc() const = 0;
  };
}
