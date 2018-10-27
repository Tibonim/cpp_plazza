#pragma once

#include <list>
#include "scopeLock.hh"
#include "conditionnal.hh"
#include "mutex.hh"
#include "nonCopyable.hh"
#include "ICom.hpp"

namespace	plazza {
  template<typename T>
  class		taskQueue : private utils::nonCopyable {
  public:
    void	pushInQueue(utils::mutex& mutex,
			    T const& protocol);
    int		popInQueue(utils::mutex& mutex,
			   T& proto);
    bool	isEmpty() const;
  private:
    std::list<T>		_taskQueue;
  };

  template<typename T>
  void		taskQueue<T>::pushInQueue(utils::mutex& mutex,
					  T const& proto) {
    utils::scopeLock	scope{ mutex };
    _taskQueue.push_back(proto);
  }

  template<typename T>
  int		taskQueue<T>::popInQueue(utils::mutex& mutex,
					 T& proto) {
    utils::scopeLock	scope{ mutex };
    if (_taskQueue.empty())
      return -1;
    proto = _taskQueue.front();
    _taskQueue.pop_front();
    return 0;
  }

  template<typename T>
  bool		taskQueue<T>::isEmpty() const {
    return _taskQueue.empty();
  }
}
