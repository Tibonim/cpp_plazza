#pragma once

#include <pthread.h>
#include "mutex.hh"

namespace	utils {
  class		scopeLock {
  public:
    scopeLock(mutex& mutex);
    ~scopeLock();
  private:
    mutex	*_mutex;
  };
}
