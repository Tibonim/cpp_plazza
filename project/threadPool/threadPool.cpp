#include <thread>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include "scopeLock.hh"
#include "threadPool.hh"

namespace	plazza {
  threadPool::threadPool(std::size_t nbrThread, void *(*) (void *))
    : _barrier{ nbrThread}, _isNotified { false } {
  }

  void		threadPool::createThread(std::size_t nbrThread,
					 void *(*function) (void *)) {
    for (std::size_t nbr = 0; nbr < nbrThread; ++nbr)
      _threadPool.push_back(thread{ function,
	    reinterpret_cast<void *>(&_barrier) });
  }

  void		threadPool::notifyAll() {
    _condCons.notifyAll();
    _isNotified = true;
  }

  int		threadPool::sendTask(threadPool::proto_t const& proto) {
    while (!_queue.isEmpty())
      _condCons.notifyOne();
    _isNotified = false;
    _queue.pushInQueue(_mutexTask, proto);
    utils::scopeLock	lock{ _mutexTask };
    _condCons.notifyOne();
    return 0;
  }

  int		threadPool::getTask(threadPool::proto_t& proto) {
    utils::scopeLock	lock{ _mutex };
    if (_queue.isEmpty()) {
      _condCons.wait(_mutex);
    }
    auto ret = _queue.popInQueue(_mutexTask, proto);
    return ret;
  }

  threadPool::~threadPool() {
    for (auto it : _threadPool)
      it.join();
  }
}
