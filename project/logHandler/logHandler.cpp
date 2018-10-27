#include <fstream>
#include <iostream>
#include "logHandler.hh"

namespace	plazza {
  logHandler::logHandler() :
    _logFileName{ "log.plazza" },
    _ofs{ "log.plazza", std::ofstream::out | std::ofstream::trunc } {
  }

  void	logHandler::push(std::string const& value) {
    _ofs << value << std::endl;
  }

  logHandler::~logHandler() {
    _ofs.close();
  }
}
