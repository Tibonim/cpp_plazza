#pragma once

#include <functional>
#include <memory>
#include "ICom.hpp"
#include "nonCopyable.hh"
#include "Factory.hpp"

namespace	plazza {
  class		comFactory : private utils::nonCopyable {
    typedef std::unique_ptr<com::ICom>	ptrCom_t;
    typedef std::function<ptrCom_t(std::size_t, std::size_t)>	func_t;
  public:
    comFactory(std::size_t portIn);
    ptrCom_t	createCommunication(std::string const& comWay);
  private:
    template<typename T, typename... Arg>
    ptrCom_t	createCom(Arg&&... args) const;
  private:
    Factory<ptrCom_t, func_t>		_factory;
    std::size_t				_id;
    std::size_t				_portIn;
    std::size_t				_portOut;
    bool				_isSwapped;
  };
}
