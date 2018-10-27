#pragma once

#include <cstdlib>
#include <sys/time.h>

namespace	utils {
  class		timeElaps {
  public:
    timeElaps(std::size_t seconds);
    ~timeElaps();
    struct timespec	*nativeHandle() const;
  private:
    struct timespec	*_time;
  };
}
