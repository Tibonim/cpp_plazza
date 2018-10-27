#pragma once

#include <pthread.h>

namespace	utils {
  class		mutex {
  public:
    mutex();
    ~mutex();
    int			lock();
    int			unlock();
    int			tryLock();
    pthread_mutex_t	*nativeHandle() const;
  private:
    pthread_mutex_t	*_mutex;
  };
}
