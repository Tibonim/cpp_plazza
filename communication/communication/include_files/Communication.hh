#pragma once

#include <memory>
#include <string>
#include "InterCom.hh"
#include "comFactory.hh"
#include "Factory.hpp"
#include "nonCopyable.hh"
#include "ICom.hpp"

namespace	com {
  class		Communication : private utils::nonCopyable {
    typedef std::unique_ptr<ICom>	ptrCom_t;
    typedef std::unique_ptr<InterCom>	InterComPtr_t;
  public:
    Communication(std::string const& comWay, std::size_t portIn = 4242);
    InterComPtr_t	createComFather();
    InterComPtr_t	createComChild();
  private:
    plazza::comFactory	_factory;
    ptrCom_t		_in;
    ptrCom_t		_out;
    std::string		_comWay;
  };
}
