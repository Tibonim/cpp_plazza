#include "scopeLock.hh"

namespace	utils {
  scopeLock::scopeLock(mutex& mutex) : _mutex{ &mutex } {
    _mutex->lock();
  }

  scopeLock::~scopeLock() {
    _mutex->unlock();
  }
}
