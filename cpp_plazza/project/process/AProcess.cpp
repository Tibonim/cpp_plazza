#include <iostream>
#include <sys/types.h>
#include <chrono>
#include <unistd.h>
#include "AProcess.hh"

namespace	plazza {
  AProcess::AProcess(std::size_t nbrThread) : _nbrThread{ nbrThread } {
    _id = getpid();
  }

  bool	AProcess::waitForInst(com::ICom::SendProtocol& proto,
			      com::InterCom *comm) {
    proto.type = com::ICom::Status::BUSY;
    std::chrono::time_point<std::chrono::system_clock>	start;
    std::chrono::time_point<std::chrono::system_clock>	end;
    start = std::chrono::system_clock::now();
    end = start;
    std::chrono::duration<double>	elapsedTime{ end - start };
    while (elapsedTime.count() < 5.f) {
      (*comm) >> proto;
      if (proto.type != com::ICom::Status::BUSY)
	return true;
      end = std::chrono::system_clock::now();
      elapsedTime = end - start;
    }
    return false;
  }

  std::size_t	AProcess::getPid() const {
    return _id;
  }

  void		AProcess::setId(std::size_t id) {
    _id = id;
  }
}
