#pragma once

#include <iostream>
#include <cstdint>
#include "IDecrypt.hh"

namespace utils {

  class Xor : public IDecrypt<std::string const &> {
  public:
    Xor();
    std::string		decrypt(std::string const &, std::string const &) const;
    std::string		encrypt(std::string const &, std::string const &) const;
    ~Xor();
  private:
    std::string		_algorithm(std::string const &, std::string const &) const;
  };
}
