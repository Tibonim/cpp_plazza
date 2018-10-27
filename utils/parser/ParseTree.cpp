#include "ParseTree.hh"

namespace	utils {
  ParseTree::ParseTree(Format const *format) : _info{ "", format } {}

  void		ParseTree::insert() {
    _info.insert(ParseInput::_parse);
  }

  void		ParseTree::feedProtocol(com::ICom::SendProtocol& protocol) const {
    _info.feedProtocol(protocol);
  }
}
