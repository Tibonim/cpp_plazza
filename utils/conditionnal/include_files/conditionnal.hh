#pragma once

#include "mutex.hh"
#include <pthread.h>

namespace	utils {
  class		conditionnal {
  public:
    conditionnal();
    int		wait(mutex const& mutex);
    int		waitUntil(mutex const& mutex, std::size_t sec);
    int		notifyOne();
    int		notifyAll();
    ~conditionnal();
  private:
    pthread_cond_t	*_condVar;
  };
}
