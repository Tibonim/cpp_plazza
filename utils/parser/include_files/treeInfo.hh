#pragma once

#include <memory>
#include "nonCopyable.hh"
#include "ICom.hpp"
#include "Format.hh"

namespace	utils {
  class		treeInfo : private nonCopyable {
    typedef std::unique_ptr<treeInfo>	infoPtr_t;
  public:
    treeInfo(std::string const& str, Format const *format);
    void	insert(std::string const& info);
    void	remove(std::string const& info);
    std::string const	&find(std::string const& str) const;
    void	feedProtocol(com::ICom::SendProtocol& protocol) const;
  private:
    void	insertRight(std::string const& info);
    void	insertLeft(std::string const& info);
    void	feedInfo(com::ICom::SendProtocol& protocol) const;
    void	feedFileName(com::ICom::SendProtocol& protocol) const;
  private:
    Format const	*_format;
    std::string		_str;
    infoPtr_t		_right;
    infoPtr_t		_left;
  };
}
