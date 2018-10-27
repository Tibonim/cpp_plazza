#pragma once

namespace utils {

  template<typename T>
  class IDecrypt {
  public:
    virtual std::string	decrypt(std::string const &, T) const = 0;
    virtual std::string	encrypt(std::string const &, T) const = 0;
    virtual ~IDecrypt() {};
  private:
  };
}
