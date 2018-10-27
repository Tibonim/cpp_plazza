#pragma once

#include <utility>
#include <memory>
#include <vector>
#include "barrier.hh"
#include "nonCopyable.hh"
#include "conditionnal.hh"
#include "taskQueue.hpp"
#include "mutex.hh"
#include "thread.hh"

namespace	plazza {
  class		threadPool : private utils::nonCopyable {
    typedef com::ICom::SendProtocol	proto_t;
  public:
    threadPool(std::size_t nbrThread, void *(*function) (void *));
    ~threadPool();
    int		sendTask(proto_t const& protocol);
    int		getTask(proto_t& protocol);
    void	notifyAll();
    void	createThread(std::size_t nbrThread, void *(*function) (void *));
  private:
    std::vector<plazza::thread>		_threadPool;
    utils::barrier			_barrier;
    utils::conditionnal			_varCond;
    utils::conditionnal			_condCons;
    utils::mutex			_mutex;
    utils::mutex			_mutexTask;
    utils::mutex			_mutexQueue;
    taskQueue<proto_t>			_queue;
    bool				_isNotified;
  };
}
