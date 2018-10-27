#pragma once

#include <list>
#include <map>
#include "logHandler.hh"
#include "taskQueue.hpp"
#include "Format.hh"
#include "dataHolder.hh"
#include "conditionnal.hh"
#include "InterCom.hh"
#include "ICom.hpp"
#include "Communication.hh"
#include "AProcess.hh"

namespace	plazza {
  class		FatherProcess : public AProcess {
    typedef std::unique_ptr<IProcess>		procPtr_t;
    typedef std::unique_ptr<com::InterCom>	comProc_t;
    typedef std::map<std::size_t, comProc_t>::iterator	iterator_t;
  public:
    FatherProcess(std::size_t nbrThread, utils::Format const& format,
		  std::string const& comWay);
    void	run() override;
    ~FatherProcess();
  private:
    bool	broadProtocol(com::ICom::SendProtocol& protocol);
    bool	readLine();
    void	*startCom(void *);
    void	getProtocol(com::ICom::SendProtocol& protocol);
    void	createProc();
    void	closeSignal();
    IProcess	*createChildProcess(com::InterCom *child,
				    com::InterCom *father,
				    std::size_t nbrThread) const;
    void	deleteProc(iterator_t itWrite, iterator_t itRead);
    void	runChild();
    void	*manageProcess(void *arg);
    void	manageChild();
    void	storeInfos(iterator_t itRead,
			   com::ICom::SendProtocol const& proto);
    void	displayInfos() const;
    bool	eraseIterator(iterator_t itRead);
  private:
    dataHolder					_holder;
    std::list<com::ICom::SendProtocol>		_taskQueue;
    const utils::Format				*_formatPtr;
    std::map<std::size_t, IProcess *>		_proc;
    std::map<std::size_t, comProc_t>		_comRead;
    std::map<std::size_t, comProc_t>		_comWrite;
    com::Communication				_communication;
    bool					_quit;
    comProc_t					_comChild;
    comProc_t					_comFather;
    bool					_isWaiting;
    std::size_t					_id;
    utils::mutex				_mutex;
    utils::conditionnal				_processHandler;
    std::map<std::size_t, std::size_t>		_counters;
    std::map<std::size_t, std::size_t>		_pid;
    std::list<std::string>			_queue;
    thread					*_handlerThread;
    bool					_closeSignal;
    logHandler					_handlerLog;
  };
}
