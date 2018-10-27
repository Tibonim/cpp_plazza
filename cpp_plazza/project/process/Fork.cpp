#include <unistd.h>
#include <iostream>
#include "ForkException.hh"
#include "ChildProcess.hh"
#include "Fork.hh"

namespace	plazza {
  Fork::Fork() {
    _pid = fork();
    if (_pid == -1)
      throw ForkException{ "Error, cannot fork", "Fork::Fork" };
  }

  pid_t	Fork::getPid() const {
    return _pid;
  }
}
