#include <iostream>
#include "CustomException.hh"
#include "launcher.hh"

int		main(int const ac, char const **av) {
  if (ac < 2) {
    std::cerr << "Usage: " << av[0] << " nbr_thread" << std::endl;
    return 0;
  }
  try {
    plazza::launcher	launcher{ ac, av };
  }
  catch (plazza::CustomException const& bad) {
    std::cerr << bad.what() << " in " << bad.where() << std::endl;
  }
}
