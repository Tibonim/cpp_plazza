#pragma once

#include <vector>
#include <functional>
#include <memory>
#include "ICom.hpp"
#include "InterCom.hh"
#include "IParser.hpp"
#include "ICom.hpp"
#include "IProcess.hpp"
#include "thread.hh"

namespace	plazza {
  class		AProcess : public IProcess {
    typedef std::unique_ptr<utils::IParser>	parserPtr_t;
  public:
    AProcess(std::size_t nbrThread);
    virtual	~AProcess() = default;
    virtual void	run() = 0;
    std::size_t		getPid() const override;
    virtual void	setId(std::size_t id) override;
  protected:
    bool		waitForInst(com::ICom::SendProtocol& proto,
				    com::InterCom *comm);
  protected:
    std::size_t		_id;
    parserPtr_t		_parser;
    std::size_t		_nbrThread;
  };
}
