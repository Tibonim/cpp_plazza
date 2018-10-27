#include "Xor.hh"

namespace utils {

  Xor::Xor()
  {
  }

  Xor::~Xor()
  {
  }

  std::string	Xor::decrypt(std::string const &input, std::string const &key) const {
    return this->_algorithm(input, key);
  }

  std::string	Xor::encrypt(std::string const &input, std::string const &key) const {
    return this->_algorithm(input, key);
  }

  std::string	Xor::_algorithm(std::string const &input, std::string const &key) const {
    unsigned i = 0;
    std::string res{""};
    for (auto it = input.begin(); it < input.end(); it++, ++i)
      {
	i %= key.size();
	res += static_cast<char>(*it ^ key[i]);
      }
    return res;
  }
}
