#include <cstddef>
#include <utility>
#include "treeInfoException.hh"
#include "treeInfo.hh"

namespace	utils {
  treeInfo::treeInfo(std::string const& str, Format const *format)
    : _format{ format }, _str{ str } {
      _right = nullptr;
      _left = nullptr;
  }

  std::string const	&treeInfo::find(std::string const& info) const {
    if (_str == info)
      return _str;
    if (_right)
      _right->find(info);
    if (_left)
      _left->find(info);
    throw plazza::treeInfoException{ "Error, " + info + std::string(" not found"),
	"treeInfo::find" };
  }

  void	treeInfo::feedInfo(com::ICom::SendProtocol& protocol) const {
    if (_right == nullptr) {
      protocol.information += _str;
      return ;
    }
    _right->feedInfo(protocol);
    protocol.information += ' ' + _str;
  }

  void	treeInfo::feedFileName(com::ICom::SendProtocol& protocol) const {
    if (_left == nullptr) {
      protocol.fileName += _str;
      return ;
    }
    _left->feedFileName(protocol);
    protocol.fileName += ' ' + _str;
  }

  void	treeInfo::feedProtocol(com::ICom::SendProtocol& protocol) const {
    feedInfo(protocol);
    feedFileName(protocol);
  }

  void	treeInfo::remove(std::string const& info) {
    if (info == _right->_str)
      _right = std::move(_right->_right);
    else if (info == _left->_str)
      _left = std::move(_left->_left);
    if (_left)
      _left->remove(info);
    if (_right)
      _right->remove(info);
  }

  void	treeInfo::insert(std::string const& info) {
    if (_format->find(info) != "")
      insertRight(info);
    else
      insertLeft(info);
  }

  void	treeInfo::insertRight(std::string const& info) {
    if (_right == nullptr) {
      treeInfo::infoPtr_t	ptrTemp{ new treeInfo{ info, _format } };
      _right = std::move(ptrTemp);
      return ;
    }
    _right->insertRight(info);
  }

  void	treeInfo::insertLeft(std::string const& info) {
    if (_left == nullptr) {
      treeInfo::infoPtr_t	ptrTemp{ new treeInfo{ info, _format } };
      _left = std::move(ptrTemp);
      return ;
    }
    _left->insertLeft(info);
  }
}
