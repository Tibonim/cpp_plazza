#include "serialization.hh"
#include <iostream>

namespace	com {
  Serialize::Serialize() : _i{ 0 } {}

  void		Serialize::SerializeCmd(com::ICom::SendProtocol const& lhs,
					com::ICom::socketProtocol& rhs) {
    rhs.remaining = 0;
    for (std::size_t i = 0; i < MAX_MSG + 1; ++i) {
      rhs.fileName[i] = 0;
      rhs.information[i] = 0;
    }
    std::size_t	iTmp{ _i };
    if (lhs.information.size() > lhs.fileName.size()){
    rhs.remaining += convertStringToInt(lhs.fileName, rhs.fileName);
    _i = iTmp;
    rhs.remaining += convertStringToInt(lhs.information, rhs.information);
    }
    else {
    rhs.remaining += convertStringToInt(lhs.information, rhs.information);
    _i = iTmp;
    rhs.remaining += convertStringToInt(lhs.fileName, rhs.fileName);
    }
  }

  void		Serialize::SerializeCmd(com::ICom::socketProtocol const& lhs,
					com::ICom::SendProtocol& rhs) const {
    convertIntToString(lhs.fileName, rhs.fileName);
    convertIntToString(lhs.information, rhs.information);
  }

  std::size_t	Serialize::convertIntToString(uint8_t const *convert,
					      std::string& toConvert) const {
    for (std::size_t i = 0; convert[i]; ++i) {
      toConvert += static_cast<char>(convert[i]);
    }
    return 0;
  }

  std::size_t	Serialize::convertStringToInt(std::string const& str,
					      uint8_t *toConvert) {
    std::size_t	cptTmp{ _i };
    std::size_t	cptConvert{};
    for (; _i < cptTmp + MAX_MSG; ++_i) {
      if (str.size() > _i)
	toConvert[cptConvert] = static_cast<uint8_t>(str[_i]);
      else {
	toConvert[cptConvert] = 0;
	return 0;
      }
      ++cptConvert;
    }
    toConvert[cptConvert] = 0;
    if (str.size() > _i)
      return str.size() - _i;
    return 0;
  }
}
