#pragma once

#include <string>
#include <map>
#include "nonCopyable.hh"

namespace	plazza {
  class		launcher : private utils::nonCopyable {
    typedef void	(launcher::*Comm_t) (std::string&) const;
  public:
    launcher(const int ac, const char **av);
  private:
    void	loadSocketInternet(std::string& option) const;
    void	loadSocketUnix(std::string& option) const;
    void	loadPipe(std::string& option) const;
    void	getCommunicationWay(const char **av);
  private:
    std::map<std::string, Comm_t>	_comWayContainer;
    int					_nbrThread;
    std::string				_comWay;
  };
}
