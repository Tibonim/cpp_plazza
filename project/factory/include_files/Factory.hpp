#pragma once

#include <map>
#include <string>
#include <memory>
#include <initializer_list>
#include <utility>
#include "FactoryException.hh"
#include "nonCopyable.hh"

namespace	plazza {
  template<typename T, typename Func>
  class		Factory : private utils::nonCopyable {
  public:
    Factory() = default;
    void	registerKey(std::string const& key, Func const& value);
    template<typename... Arg>
    T		create(std::string const& key, Arg&&... args) const;
  private:
    std::map<std::string, Func>	_factory;
  };

  template<typename T, typename Func> template<typename... Arg>
  T	Factory<T, Func>::create(std::string const& key,
				 Arg&&... args) const
  {
    auto const&	it = _factory.find(key);
    if (it == _factory.end())
      throw FactoryException{ "Error, key not found", "Factory::create" };
    return it->second(std::forward<Arg>(args)...);
  }

  template<typename T, typename Func>
  void	Factory<T, Func>::registerKey(std::string const& key, Func const& value) {
    auto const& it = _factory.find(key);
    if (it == _factory.end())
      _factory[key] = value;
  }
}
