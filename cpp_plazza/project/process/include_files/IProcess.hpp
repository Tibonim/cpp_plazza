#pragma once

#include "nonCopyable.hh"

namespace	plazza {
  class		IProcess : private utils::nonCopyable {
  public:
    virtual ~IProcess() = default;
    virtual void	run() = 0;
    virtual std::size_t	getPid() const = 0;
    virtual void	setId(std::size_t id) = 0;
  };
}
