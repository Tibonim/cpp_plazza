#pragma once

#include <limits>
#include "KeyFinderException.hh"
#include "Format.hh"
#include "Regex.hh"
#include "Cesar.hh"
#include "Xor.hh"
#include "nonCopyable.hh"

namespace utils {
  class KeyFinder : public nonCopyable {
  public:
    enum class keyType : uint16_t {
      NONE,
      CESAR,
      XOR,
      NOTFOUND
    };
    typedef struct	key {
      uint8_t		cKey;
      std::string	xKey;
      keyType		type;
    }			key;
    KeyFinder();
    ~KeyFinder() = default;
     bool find(std::string const &);
     bool incrKey();
     void reset();
     key const &getKey() { return _key; };
  private:
    bool _clearFile(std::string const &);
     bool _cesarFile(std::string const &);
     bool _xorFile(std::string const &);
     bool _xor2BytesFile(std::string const &,
			 Xor &);
    void _init();
    bool _isFullPrintable(std::string const &content);

     key	  _key;
     bool	  _start;
     bool	  _clear;
     bool	  _cesar;
  };
}
