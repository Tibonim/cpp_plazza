#include <iostream>
#include "thread.hh"

namespace	plazza {
  thread::thread(void *(*func) (void *), void *arg) {
    _join = NULL;
    pthread_create(&_thread, NULL, func, arg);
  }

  int	thread::join() {
    return pthread_join(_thread, &_join);
  }

  thread::~thread() {
    if (_join)
      pthread_exit(0);
  }
}
