#include <iostream>
#include "mutex.hh"
#include "timeElaps.hh"
#include "CondException.hh"
#include "conditionnal.hh"

namespace	utils {
  conditionnal::conditionnal() {
    _condVar = new pthread_cond_t;
    if (pthread_cond_init(_condVar, NULL) != 0)
      throw plazza::CondException{ "Error while initialize cond", "conditionnal" };
  }

  int		conditionnal::wait(mutex const& mutex) {
    auto ret = pthread_cond_wait(_condVar, mutex.nativeHandle());
    return ret;
  }

  int		conditionnal::waitUntil(mutex const& mutex, std::size_t sec) {
    timeElaps	time{ sec };
    return pthread_cond_timedwait(_condVar, mutex.nativeHandle(),
				  time.nativeHandle());
  }

  int		conditionnal::notifyOne() {
    return pthread_cond_signal(_condVar);
  }

  int		conditionnal::notifyAll() {
    return pthread_cond_broadcast(_condVar);
  }

  conditionnal::~conditionnal() {
    pthread_cond_destroy(_condVar);
    delete _condVar;
  }
}
