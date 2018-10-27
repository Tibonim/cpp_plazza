#include <memory>
#include <cctype>
#include <iostream>
#include <algorithm>
#include "CustomException.hh"
#include "Format.hh"
#include "IProcess.hpp"
#include "FatherProcess.hh"
#include "launcher.hh"


namespace	plazza {
  void	launcher::loadPipe(std::string& option) const {
    option = "pipe";
  }

  void	launcher::loadSocketInternet(std::string& option) const {
    option = "socketIn";
  }

  void	launcher::loadSocketUnix(std::string& option) const {
    option = "socketUn";
  }

  void	launcher::getCommunicationWay(const char **av) {
    if (!av[2]) {
      _comWay = "pipe";
      return ;
    }
    std::string	option{ av[2] };
    auto it = _comWayContainer.find(option);
    if (it == _comWayContainer.end()) {
      _comWay = "pipe";
      return ;
    }
    (this->*it->second) (option);
    _comWay = option;
  }

  launcher::launcher(const int ac, const char **av) {
    _comWayContainer["pipe"] = &launcher::loadPipe;
    _comWayContainer["socketIn"] = &launcher::loadSocketInternet;
    _comWayContainer["socketUn"] = &launcher::loadSocketUnix;
    std::string	nbrThread{ av[1] };
    if (ac < 3)
      _comWay = "pipe";
    else
      getCommunicationWay(av);
    if (!std::all_of(nbrThread.begin(), nbrThread.end(),
		     [] (char c) { return std::isdigit(c) || c == '-'; }))
      throw CustomException{ "Error: Usage : ./plazza nbr_thread",
	  "launcher::launcher" };
    try {
      _nbrThread = std::stoi(nbrThread);
    }
    catch (std::out_of_range const& out) {
      throw CustomException{ "Error : thread's number out of range",
	  "launcher::launcher" };
    }
    if (_nbrThread < 0)
      throw CustomException{ "Error: invalid argument", "launcher::launcher" };
    std::size_t	threadNbr{ static_cast<std::size_t>(_nbrThread) };
    utils::Format	format;
    std::unique_ptr<IProcess>	process{ new FatherProcess{ threadNbr, format,
	  _comWay }};
    process->run();
  }
}
