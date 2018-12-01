#include "time.h"
#include "io.h"
#include <iostream>
#include <iomanip>

std::string basename(std::string const& path) {
  return path.substr(path.find_last_of("/\\") + 1);
}

void print_usage(std::string const& name) {
  std::cout << "Usage: " << basename(name) << " [options] file [time1 time2 ...]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << std::setw(20) << std::left << "  --version" << "Display program version and exit." << std::endl;
  std::cout << std::setw(20) << std::left << "  --help" << "Display usage information and exit." << std::endl;
  std::cout << "Example:" << std::endl;
  std::cout << "  " << basename(name) << " log.txt 1:27 -11:01 +2:15:23 127" << std::endl;
}

int main(int argc, char **argv) {
  // if no argument supplied, exit here
  if (argc <= 1) {
    print_usage(argv[0]);

    return 0;
  }

  // parse first argument
  if (argc >= 2) {
    std::string firstArgument = std::string(argv[1]);

    // check if version
    if (firstArgument == "--version") {
      std::cout << "timetrack " VERSION << std::endl;
      std::cout << "Copyright (C) 2018 Andrei Nemes" << std::endl; 
      
      std::cout << "This is free software; see the source for copying conditions.  There is NO" << std::endl;
      std::cout << "WARRANTY; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << std::endl;

      return 0;
    }

    // check if help
    if (firstArgument == "--help") {
      print_usage(argv[0]);

      return 0;
    }
  }

  // read and print current time
  Time current = getTime(argv[1]);

  std::cout << std::endl;
  std::cout << std::setw(10) << current << std::endl;

  if (argc <= 2) {
    // if we have no operands, exit
    return 0;
  }

  Time result(current.getTime()); // todo: copy constructor
  Time difference;

  // loop through the operands and add them to the total, and difference
  for(int i = 2; i < argc; i++) {
    Time operand = Time(argv[i]);
    std::string operation(operand.getTime() > 0 ? "+" : "");

    result = result + operand;
    difference = difference + operand;

    std::cout << std::setw(10) << operation + operand.toString() << std::endl;
  }

  std::string separator = std::string(8, '-');

  std::cout << std::setw(10) << separator << std::endl;
  std::cout << std::setw(10) << result << std::endl;
  std::cout << std::endl;

  bool ok = putTime(argv[1], result, difference);
  if (ok) {
    std::cout << "Wrote to '" << argv[1] << "'." << std::endl;
    return 0;
  } else {
    std::cout << "Couldn't write to '" << argv[1] << "'." << std::endl;
    return 1;
  }
}
