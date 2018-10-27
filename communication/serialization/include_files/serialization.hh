#pragma once

#include "nonCopyable.hh"
#include "ICom.hpp"

namespace	com {
  class		Serialize : private utils::nonCopyable {
  public:
    Serialize();
    void	SerializeCmd(com::ICom::SendProtocol const& lhs,
			     com::ICom::socketProtocol& rhs);
    void	SerializeCmd(com::ICom::socketProtocol const& lhs,
			     com::ICom::SendProtocol& rhs) const;
  private:
    std::size_t	convertStringToInt(std::string const& str,
				   uint8_t *toConvert);
    std::size_t	convertIntToString(uint8_t const *convert,
				   std::string& toConvert) const;
  private:
    std::size_t	_i;
  };
}
