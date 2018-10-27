#pragma once

#include <unistd.h>
#include <utility>
#include <memory>
#include "Communication.hh"
#include "IProcess.hpp"

namespace	plazza {
  class		Fork : private utils::nonCopyable {
  public:
    Fork();
    pid_t	getPid() const;
  private:
    pid_t	_pid;
  };
}
