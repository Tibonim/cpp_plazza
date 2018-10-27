#include <iostream>
#include "Communication.hh"

namespace	com {

  Communication::Communication(std::string const &comWay, std::size_t portIn)
    : _factory{ portIn }{
    _comWay = comWay;
  }

  Communication::InterComPtr_t	Communication::createComFather() {
    _in = _factory.createCommunication(_comWay);
    return InterComPtr_t{ new InterCom{_in} };
  }

  Communication::InterComPtr_t	Communication::createComChild() {
    _out = _factory.createCommunication(_comWay);
    return InterComPtr_t{ new InterCom{_out} };
  }
}
