//
// main.cpp for main in /home/bouger_t/cpp_plazza/communication/intSocket
//
// Made by thibault bougerolles
// Login   <bouger_t@epitech.net>
//
// Started on  Thu Apr  7 00:18:40 2016 thibault bougerolles
// Last update Mon Apr 11 20:11:02 2016 thibault bougerolles
//

#include <iostream>
#include "intSocket.hh"

#include <string.h>

int main()
{
  com::ICom	*udp = new com::intSocket{ 1, 8500, 8000};
  com::ICom::SendProtocol	proto;

  proto.type = com::ICom::Status::BUSY;
  proto.information = "lelzerzerzerzerzerzerzerzerzerzerzerlzerzerzerzerzerzerzerzerzerzerzerlzerzerzerzerzerzerzerzerzerzerzerlzerzerzerzerzerzerzerzerzerzerzerlzerzerzerzerzerzerzerzerzerzerzerlzerzerzerzerzerzerzerzerzerzerzerlzerzerzerzerzerzerzerzerzerzerzerlzerzerzerzerzerzerzerzerzerzerzerlzerzerzerzerzerzerzerzerzerzerzerok";
  proto.fileName = "niquel";
  udp->sendCmd(proto);
  delete udp;
}
