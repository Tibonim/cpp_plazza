#pragma once

#include <iostream>
#include <limits>
#include "DataFinderException.hh"
#include "Format.hh"
#include "Regex.hh"
#include "Cesar.hh"
#include "Xor.hh"
#include "KeyFinder.hh"
#include "nonCopyable.hh"

namespace utils {
  class DataFinder : public nonCopyable {
  public:
    DataFinder(Format &);
    ~DataFinder() {};
    void find(std::string const &, std::string const &);
    std::vector<std::string> const &getOccurences() const;
  private:
    typedef bool (DataFinder::*f)(std::string const &,
				  KeyFinder::key const &) const;
    std::string _preFind(std::string const &, std::string const &) const;
    bool _notFound(std::string const &,
		   KeyFinder::key const &) const;
    bool _xorFile(std::string const &,
		  KeyFinder::key const &) const;
    bool _cesarFile(std::string const &,
		    KeyFinder::key const &) const;
    bool _extractData(std::string const &) const;

    void _bruteForce(std::string const &) const;
    bool _bruteCesar(std::string const &) const;
    bool _bruteXor(std::string const &) const;
    bool _bruteClear(std::string const &) const;

    Format *_format;
    std::map<KeyFinder::keyType, f>	_actions;
    Regex				*_r;
  };
}
