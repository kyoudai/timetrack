#include "time.h"
#include "io.h"
#include <iostream>
#include <iomanip>

std::string basename(std::string const& path) {
  return path.substr(path.find_last_of("/\\") + 1);
}

int main(int argc, char **argv) {
  // if no argument supplied, exit here
  if (argc <= 1) {
    std::cout << "Usage: " << basename(argv[0]) << " [options] file [time1 time2 ...]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::setw(20) << std::left << "  --version" << "Display program version and exit." << std::endl;

    return 0;
  }

  // parse version argument
  if (argc >= 2) {
    std::string arg = std::string(argv[1]);

    if (arg == "--version" || arg == "-v") {
      std::cout << "timetrack " VERSION << std::endl;
      std::cout << "Copyright (C) 2018 Andrei Nemes" << std::endl; 
      
      std::cout << "This is free software; see the source for copying conditions.  There is NO" << std::endl;
      std::cout << "WARRANTY; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << std::endl;

      return 0;
    }
  }

  // otherwise, carry on with the rest
  Time current = getTime(argv[1]);

  std::cout << std::endl;
  std::cout << std::setw(10) << current << std::endl;

  if (argc <= 2) {
    return 0;
  }

  Time result(current.getTime()); // todo: copy constructor

  for(int i = 2; i < argc; i++) {
    Time operand = Time(argv[i]);
    std::string operation(operand.getTime() > 0 ? "+" : "");
    result = result + operand;

    std::cout << std::setw(10) << operation + operand.toString() << std::endl;
  }

  std::string separator = std::string(8, '-');

  std::cout << std::setw(10) << separator << std::endl;
  std::cout << std::setw(10) << result << std::endl;
  std::cout << std::endl;

  bool ok = putTime(argv[1], result);
  if (ok) {
    std::cout << "Wrote to '" << argv[1] << "'." << std::endl;
    return 0;
  } else {
    std::cout << "Couldn't write to '" << argv[1] << "'." << std::endl;
    return 1;
  }
}
