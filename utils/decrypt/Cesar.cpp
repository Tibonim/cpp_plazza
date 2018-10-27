#include "Cesar.hh"

namespace utils {

  Cesar::Cesar()
  {
  }

  Cesar::~Cesar()
  {
  }

  std::string	Cesar::decrypt(std::string const &input, uint8_t key) const {
    return this->_loop(input, key, -1);
  }

  std::string	Cesar::encrypt(std::string const &input, uint8_t key) const {
    return this->_loop(input, key, 1);
  }

  std::string	Cesar::_loop(std::string const &input, uint8_t key, int op) const {
    std::string res{""};
    for (auto it = input.begin(); it < input.end(); it++)
      res += static_cast<char>(*it + (static_cast<int>(key) * op));
    return res;
  }
}
