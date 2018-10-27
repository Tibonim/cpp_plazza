#pragma once

#include <iostream>
#include <cstdint>
#include "IDecrypt.hh"

namespace utils {

  class Cesar : public IDecrypt<uint8_t> {
  public:
    Cesar();
    std::string		decrypt(std::string const &, uint8_t) const;
    std::string		encrypt(std::string const &, uint8_t) const;
    ~Cesar();
  private:
    std::string		_loop(std::string const &, uint8_t, int) const;
  };
}
