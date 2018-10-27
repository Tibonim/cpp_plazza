#include <utility>
#include <iostream>
#include <string>
#include "unixSocket.hh"
#include "fifoPipes.hh"
#include "intSocket.hh"
#include "comFactory.hh"

namespace	plazza {
  comFactory::comFactory(std::size_t portIn)
    : _id { 0 }, _portIn{ portIn } {
    _factory.registerKey("pipe",
    			 [this](std::size_t id, std::size_t in){
    			   return this->createCom<com::NamedPipe>(id, in);
    			 });
    _factory.registerKey("socketIn",
    			 [this](std::size_t id, std::size_t in) {
    			   return this->createCom<com::intSocket>(id, in);
    			 });
    _factory.registerKey("socketUn",
    			 [this](std::size_t id, std::size_t in) {
    			   return this->createCom<com::unixSocket>(id, in);
    			 });
    _isSwapped = false;
  }

  comFactory::ptrCom_t	comFactory::createCommunication(std::string const& comWay) {
    std::size_t	id{ _id };
    std::size_t	portIn{ _portIn };
    // if ((_portIn < _portOut || !(_id % 2)) && _id) {
    //   std::swap(_portIn, _portOut);
    //   _isSwapped = false;
    // }
    // else if (_portIn > _portOut && (_id % 2) && _id) {
    //   std::swap(_portIn, _portOut);
    //   _portIn++;
    //   _portOut++;
    //   portIn = _portIn;
    //   portOut = _portOut;
    // }
    // portIn = _portIn;
    // portOut = _portOut;
    // _isSwapped = true;
    ++_portIn;
    ++_id;
    return _factory.create(comWay, id, portIn);
  }

  template<typename T, typename... Arg>
  comFactory::ptrCom_t	comFactory::createCom(Arg&&... args) const {
    return ptrCom_t(new T(std::forward<Arg>(args)...));
  }
}
