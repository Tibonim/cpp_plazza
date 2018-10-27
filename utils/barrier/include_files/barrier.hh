#pragma once

#include <pthread.h>
#include "nonCopyable.hh"

namespace	utils {
  class		barrier {
  public:
    barrier(std::size_t nbrThread);
    ~barrier();
    int			wait();
  private:
    pthread_barrier_t	*_barrier;
  };
}
