#pragma once

#include <memory>
#include "nonCopyable.hh"
#include "ICom.hpp"

namespace	com {
  class		InterCom : private utils::nonCopyable {
    typedef std::unique_ptr<com::ICom>	ptrCom_t;
  public:
    InterCom(ptrCom_t& com);
    InterCom	&operator<<(com::ICom::SendProtocol const& protocol);
    InterCom	&operator>>(com::ICom::SendProtocol& protocol);
    void	send(com::ICom::SendProtocol const& protocol);
    void	receive(com::ICom::SendProtocol& protocol);
  private:
    ptrCom_t	_comWay;
  };
}
