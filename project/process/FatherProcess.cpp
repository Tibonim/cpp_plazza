#include <utility>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <iostream>
#include <string>
#include "thread.hh"
#include "CustomException.hh"
#include "ChildProcess.hh"
#include "Fork.hh"
#include "scopeLock.hh"
#include "ICom.hpp"
#include "ParseTree.hh"
#include "ParseInput.hh"
#include "FatherProcess.hh"

namespace	plazza {
  FatherProcess::FatherProcess(std::size_t nbrProc,
			       utils::Format const& format,
			       std::string const& comWay)
    : AProcess(nbrProc),
      _holder{ format },
      _formatPtr{ &format },
      _communication{ comWay },
      _quit{ false }, _isWaiting{ false }, _id{ 0 } {
    std::unique_ptr<utils::IParser>	parser{ new utils::ParseInput };
    _parser = std::move(parser);
    _closeSignal = false;
  }

  void	FatherProcess::getProtocol(com::ICom::SendProtocol& protocol) {
    std::unique_ptr<utils::IParser> treeParser(new utils::ParseTree{ _formatPtr });
    _holder.setParser(std::move(treeParser));
    _holder.insertInTree();
    _holder.feedProtocol(protocol);
    std::unique_ptr<utils::IParser>	inputParser{ new utils::ParseInput{} };
    if (protocol.information == "")
      return ;
    std::string	value{ "empty" };
    inputParser->clearString(protocol.fileName);
    inputParser->clearString(protocol.information);
    inputParser->setString(protocol.fileName);
    while (value != "") {
      inputParser->parse(' ');
      if (inputParser->getString() != "") {
	com::ICom::SendProtocol	proto;
	proto.fileName = inputParser->getString();
	proto.information = protocol.information;
	proto.type = com::ICom::Status::AVAILABLE;
	_taskQueue.push_back(proto);
      }
      value = inputParser->getString();
    }
  }

  bool	FatherProcess::readLine() {
    std::string	line{};
    if (!std::getline(std::cin, line))
      return false;
    else if (line == "exit")
      return false;
    std::cin.clear();
    std::unique_ptr<utils::IParser>	parser{ new utils::ParseInput() };
    _holder.setParser(std::move(parser));
    _holder.parseString(line);
    while (!_holder.isEmpty()) {
      com::ICom::SendProtocol	protocol;
      getProtocol(protocol);
    }
    return true;
  }

  IProcess	*FatherProcess::createChildProcess(com::InterCom *child,
						   com::InterCom *father,
						   std::size_t nbrThread) const {
    return new ChildProcess{ child, father, nbrThread };
  }

  void		FatherProcess::runChild() {
    Fork		f;
    if (!f.getPid()) {
      auto const& it = _proc.find(_id);
      if (it == _proc.end())
	_exit(0);
      it->second->run();
      _exit(0);
    }
    else
      _pid[_id] = f.getPid();
  }

  void		FatherProcess::createProc() {
    _comChild = _communication.createComChild();
    _comFather = _communication.createComFather();
    auto proc = createChildProcess(_comChild.get(), _comFather.get(),
				   _nbrThread);
    _comWrite[_id] = std::move(_comChild);
    _comRead[_id] = std::move(_comFather);
    _proc[_id] = proc;
    _counters[_id] = 0;
    runChild();
    ++_id;
    return ;
  }

  void	FatherProcess::deleteProc(FatherProcess::iterator_t itWrite,
				  FatherProcess::iterator_t itRead) {
    if (itWrite == _comWrite.end() || itRead == _comRead.end())
      return ;
    std::size_t	key{ itWrite->first };
    auto itProc = _proc.find(key);
    auto itPid = _pid.find(key);
    if (itProc == _proc.end())
      return ;
    _comWrite.erase(itWrite);
    _comRead.erase(itRead);
    _proc.erase(itProc);
    waitpid(itPid->second, 0, 0);
    _pid.erase(itPid);
    _counters.erase(_id);
    --_id;
  }

  bool	FatherProcess::broadProtocol(com::ICom::SendProtocol& protocol) {
    try {
      bool	isSend{ false };
      for (auto it = _comWrite.begin(); it != _comWrite.end(); ++it) {
	utils::scopeLock	scope{ _mutex };
	auto	itCount = _counters.find(it->first);
	if (itCount != _counters.end() &&
	    itCount->second < 2 * AProcess::_nbrThread) {
	  isSend = true;
	  (*it->second) << protocol;
	  itCount->second++;
	}
	else
	  isSend = false;
      }
      return isSend;
    }
    catch (plazza::CustomException& bad) {
      return false;
    }
  }

  void	*FatherProcess::startCom(void *arg) {
    while (!_taskQueue.empty()) {
      com::ICom::SendProtocol	proto;
      proto = _taskQueue.front();
      if (!broadProtocol(proto))
	createProc();
      else
	_taskQueue.pop_front();
    }
    return arg;
  }

  void	FatherProcess::closeSignal() {
    try {
      com::ICom::SendProtocol	proto;
      proto.type = com::ICom::Status::CLOSED;
      proto.fileName = "";
      proto.information = "";
      _closeSignal = true;
      for (auto it = _comWrite.begin(); it != _comWrite.end(); ++it) {
	(*it->second) << proto;
	auto itPid = _pid.find(it->first);
	waitpid(itPid->second, 0, 0);
      }
      return ;
    }
    catch (CustomException const& bad) {
      std::cerr << bad.what() << " in " << bad.where() << std::endl;
    }
  }

  void	FatherProcess::storeInfos(FatherProcess::iterator_t itRead,
				  com::ICom::SendProtocol const& proto) {
    std::unique_ptr<utils::IParser>	inputParser{ new utils::ParseInput{} };
    auto itCount = _counters.find(itRead->first);
    if (itCount != _counters.end() && itCount->second > 0)
      --itCount->second;
    inputParser->setString(proto.information);
    std::string		value{ "EMPTY" };
    while (value != "") {
      inputParser->parse();
      value = inputParser->getString();
      if (value != "") {
	_handlerLog.push(value);
	_queue.push_back(value);
      }
    }
  }

  bool	FatherProcess::eraseIterator(FatherProcess::iterator_t itRead) {
    auto itReadTmp = _comRead.end();
    auto itWrite = _comWrite.end();
    itWrite = _comWrite.find(itRead->first);
    itReadTmp = itRead;
    bool	status{ false };
    if (itRead != _comRead.begin())
      --itRead;
    else
      status = true;
    deleteProc(itWrite, itReadTmp);
    if (status)
      itRead = _comRead.begin();
    if (itRead == _comRead.end())
      return false;
    return true;
  }

  void	FatherProcess::displayInfos() const {
    for (auto it : _queue)
      std::cout << it << std::endl;
  }

  void	FatherProcess::manageChild() {
    com::ICom::SendProtocol	proto { com::ICom::Status::AVAILABLE, "", "" };
    for (auto itRead = _comRead.begin(); itRead != _comRead.end();
	 ++itRead) {
      utils::scopeLock	lock{ _mutex };
      if ((itRead->second))
      	(*itRead->second) >> proto;
      if (proto.type == com::ICom::Status::FINISH)
	storeInfos(itRead, proto);
      else if (proto.type == com::ICom::Status::CLOSED && !_closeSignal) {
	if (!eraseIterator(itRead))
	  return ;
      }
    }
    displayInfos();
    _queue.clear();
  }

  void	*FatherProcess::manageProcess(void *arg) {
    while (!_isWaiting) {
      usleep(1500);
      manageChild();
    }
    manageChild();
    return arg;
  }


  void	FatherProcess::run() {
    Call<void *(void *)>::funcAdd = [this](void *value){
      return this->manageProcess(value);
    };
    void	*(*handler) (void *);
    handler = static_cast<decltype(handler)>(Call<void *(void *)>::callback);
    _handlerThread = new thread{ handler, 0 };
    while (1) {
      if (!readLine()) {
	_closeSignal = false;
	// usleep(30000);
      	return ;
      }
      startCom(0);
    }
  }

  FatherProcess::~FatherProcess() {
    closeSignal();
    waitpid(-1, 0, 0);
    _isWaiting = true;
    _handlerThread->join();
  }
}
