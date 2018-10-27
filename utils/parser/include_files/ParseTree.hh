#pragma once

#include <memory>
#include "Format.hh"
#include "treeInfo.hh"
#include "ParseInput.hh"

namespace	utils {
  class		ParseTree : public ParseInput {
  public:
    ParseTree(Format const *format);
    ~ParseTree() = default;
    void	insert() override;
    void	feedProtocol(com::ICom::SendProtocol& protocol) const override;
  private:
    treeInfo			_info;
  };
}
