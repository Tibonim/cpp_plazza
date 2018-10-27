#include <utility>
#include <iostream>
#include "InterCom.hh"

namespace	com {
  InterCom::InterCom(InterCom::ptrCom_t& com) {
    _comWay = std::move(com);
  }

  InterCom	&InterCom::operator<<(com::ICom::SendProtocol const& protocol) {
    send(protocol);
    return *this;
  }

  InterCom	&InterCom::operator>>(com::ICom::SendProtocol& protocol) {
    receive(protocol);
    return *this;
  }

  void		InterCom::send(com::ICom::SendProtocol const& protocol) {
    (*_comWay) << protocol;
  }

  void		InterCom::receive(com::ICom::SendProtocol& protocol) {
    (*_comWay) >> protocol;
    return ;
  }
}
