#pragma once

#include "conditionnal.hh"
#include "barrier.hh"
#include "InterCom.hh"
#include "threadPool.hh"
#include "ICom.hpp"
#include "mutex.hh"
#include "AProcess.hh"

namespace	plazza {
  class		ChildProcess : public AProcess {
    typedef std::unique_ptr<threadPool>		ptrPool_t;
    typedef std::unique_ptr<com::InterCom>	interComPtr_t;
  public:
    ChildProcess(com::InterCom *comm, com::InterCom *commFather,
		 std::size_t nbrThread);
    void	run() override;
    void	setId(std::size_t id) override;
  private:
    void	*routineParser(void *arg);
    void	launchPool();
    bool	launchChild();
    void	getInformations(com::ICom::SendProtocol& proto) const;
  private:
    threadPool			*_pool;
    com::InterCom		*_comm;
    com::InterCom		*_commFather;
    std::size_t			_counter;
    bool			_isSynchronized;
  };
}
