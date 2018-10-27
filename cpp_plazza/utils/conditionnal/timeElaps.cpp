#include <ctime>
#include "timeException.hh"
#include "timeElaps.hh"

namespace	utils {
  timeElaps::timeElaps(std::size_t timeInMs) {
    struct timeval	now;
    if (gettimeofday(&now, NULL) != 0)
      throw plazza::timeException{ "Error while recover the time", "timeElaps" };
    _time = new struct timespec;
    _time->tv_sec = time(NULL) + timeInMs / 1000;
    _time->tv_nsec = now.tv_usec * 1000 + 1000 * 1000 * (timeInMs % 1000);
    _time->tv_sec += _time->tv_nsec / (1000 * 1000 * 1000);
    _time->tv_nsec %= (1000 * 1000 * 1000);
  }

  timeElaps::~timeElaps() {
    delete _time;
  }

  struct timespec	*timeElaps::nativeHandle() const {
    return _time;
  }
}
