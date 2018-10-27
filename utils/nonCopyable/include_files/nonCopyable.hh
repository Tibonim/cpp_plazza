#pragma once

namespace	utils {
  class		nonCopyable {
  public:
    nonCopyable() = default;
    virtual ~nonCopyable() = default;
    nonCopyable(nonCopyable const& copy) = delete;
    nonCopyable	&operator=(nonCopyable const& copy) = delete;
  };
}
