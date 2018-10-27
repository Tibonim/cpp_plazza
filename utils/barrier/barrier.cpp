#include <cstdio>
#include "barrierException.hh"
#include "barrier.hh"

namespace	utils {
  barrier::barrier(std::size_t nbrThread) {
    _barrier = new pthread_barrier_t;
    if (pthread_barrier_init(_barrier, 0, nbrThread) != 0)
      throw plazza::barrierException{ "Error, cannot initialize barrier", "barrier" };
  }

  int		barrier::wait() {
    return pthread_barrier_wait(_barrier);
  }

  barrier::~barrier() {
    pthread_barrier_destroy(_barrier);
    delete _barrier;
  }
}
