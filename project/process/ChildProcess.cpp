#include <cstddef>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <utility>
#include <chrono>
#include "ChildProcess.hh"
#include "Format.hh"
#include "DataFinder.hh"
#include "CustomException.hh"

namespace	plazza {
  ChildProcess::ChildProcess(com::InterCom *comm,
			     com::InterCom *commFather,
			     std::size_t nbrThread)
    : AProcess{ nbrThread }, _counter{ 0 }, _isSynchronized{ false } {
    _comm = comm;
    _commFather = commFather;
    _counter = nbrThread;
  }

  void	ChildProcess::getInformations(com::ICom::SendProtocol& proto) const {
    try {
      utils::Format f("confDic");
      utils::DataFinder d(f);
      d.find(proto.fileName, proto.information);
      proto.information = "";
      for (auto it : d.getOccurences()) {
	proto.information += it;
	proto.information += ";";
      }
    }
    catch (CustomException const &e) {
      // std::cerr << e.what() << " in " << e.where() << std::endl;
      proto.information = "";
      proto.fileName = "";
    }
  }

  void	*ChildProcess::routineParser(void *barrier) {
    reinterpret_cast<utils::barrier *>(barrier)->wait();
    if (_isSynchronized) {
      --_counter;
      return 0;
    }
    com::ICom::SendProtocol	proto{ com::ICom::Status::BUSY, "", "" };
    if (_pool->getTask(proto) != -1 && proto.fileName != "" &&
	proto.information != "")
      getInformations(proto);
    proto.type = com::ICom::Status::FINISH;
    if (proto.information != "")
      (*_commFather) << proto;
    return routineParser(barrier);
  }

  void	ChildProcess::setId(std::size_t id) {
    AProcess::_id = id;
  }

  void	ChildProcess::launchPool() {
    Call<void *(void *)>::func = [this](void *value){
      return this->routineParser(value);
    };
    void	*(*function) (void *);
    function = static_cast<decltype(function)>(Call<void *(void *)>::callBack);
    _pool = new threadPool{ _nbrThread, function};
    _pool->createThread(_nbrThread, function);
  }

  bool	ChildProcess::launchChild() {
    com::ICom::SendProtocol	proto;
    if (waitForInst(proto, _comm)) {
      _pool->sendTask(proto);
      if (proto.type == com::ICom::Status::CLOSED) {
	// std::cout << "CLOSED SIGNAL " << getpid() << std::endl;
	while (_counter)
	  _pool->notifyAll();
	_isSynchronized = true;
	delete _pool;
	usleep(1500);
	return false;
      }
    }
    else {
      _isSynchronized = true;
      _pool->notifyAll();
      delete _pool;
      com::ICom::SendProtocol	proto{ com::ICom::Status::CLOSED,
	  "", "" };
      (*_commFather) << proto;
      return false;
    }
    return true;
  }

  void	ChildProcess::run() {
    try {
      launchPool();
      while (1) {
	if (!launchChild()) {
	  return ;
	}
      }
    }
    catch (CustomException const& bad) {
      std::cerr << bad.what() << " in " << bad.where() << std::endl;
      com::ICom::SendProtocol	proto{ com::ICom::Status::CLOSED, "", "" };
      try {
	(*_commFather) << proto;
      }
      catch (CustomException const& bad) {
	std::cout << bad.what() << " in " << bad.where() << std::endl;
      }
      _isSynchronized = true;
      _pool->notifyAll();
      delete _pool;
    }
  }
  /* END OF NAMESPACE  */
}
