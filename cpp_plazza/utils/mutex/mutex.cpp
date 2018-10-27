#include <iostream>
#include "CondException.hh"
#include "mutex.hh"

namespace	utils {
  mutex::mutex() {
    _mutex = new pthread_mutex_t;
    if (pthread_mutex_init(_mutex, NULL) != 0)
      throw plazza::CondException{ "Error while initialize mutex", "mutex" };
  }

  mutex::~mutex() {
    pthread_mutex_destroy(_mutex);
    delete _mutex;
  }

  int			mutex::lock() {
    return pthread_mutex_lock(_mutex);
  }

  int			mutex::unlock() {
    return pthread_mutex_unlock(_mutex);
  }

  int			mutex::tryLock() {
    return pthread_mutex_trylock(_mutex);
  }

  pthread_mutex_t	*mutex::nativeHandle() const {
    return _mutex;
  }
}
