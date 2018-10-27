#pragma once

#include "IParser.hpp"

namespace	utils {
  class		ParseInput : public IParser {
    typedef std::string::iterator	iterator_t;
  public:
    ParseInput() = default;
    ~ParseInput() = default;
    void		parse(char token = ';') override;
    std::string	const	&getString() const override;
    void		setString(std::string const& str) override;
    void		clearString(std::string& str) const override;
    virtual void	insert() override;
    virtual void	feedProtocol(com::ICom::SendProtocol& protocol) const override;
  private:
    void		clearIterator(char token);
  protected:
    std::string			_parse;
    std::string			_str;
    iterator_t			_first;
    iterator_t			_last;
  };
}
