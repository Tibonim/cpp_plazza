#pragma once

#include <functional>
#include <pthread.h>

namespace	plazza {
  template<typename T>
  struct	Call;

  template<typename Ret, typename Params>
  struct	Call<Ret(Params)> {
    template<typename Args>
    static Ret	callBack(Args arg) { return func(arg); };
    static std::function<Ret(Params)>	func;
    template<typename Args>
    static Ret	callback(Args arg) { return funcAdd(arg); };
    static std::function<Ret(Params)>	funcAdd;
  };

  template<typename Ret, typename Params>
  std::function<Ret(Params)>	Call<Ret(Params)>::func;

  template<typename Ret, typename Params>
  std::function<Ret(Params)>	Call<Ret(Params)>::funcAdd;

  class		thread {
  public:
    explicit thread(void *(*func) (void *), void *arg);
    int		join();
    ~thread();
  private:
    pthread_t	_thread;
    void	*_join;
  };
}
