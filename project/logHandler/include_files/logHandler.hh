#pragma once

#include <fstream>
#include <string>

namespace	plazza {
  class		logHandler {
  public:
    logHandler();
    void	push(std::string const& value);
    ~logHandler();
  private:
    std::string	_logFileName;
    std::ofstream	_ofs;
  };
}
