#include "time.h"
#include "io.h"
#include <iostream>
#include <iomanip>

std::string basename(std::string const& path) {
  return path.substr(path.find_last_of("/\\") + 1);
}

void printUsage(std::string const& name) {
  std::cout << "Usage: " << basename(name) << " [options] file [time1 time2 ...]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << std::setw(20) << std::left << "  --version" << "Display program version and exit." << std::endl;
  std::cout << std::setw(20) << std::left << "  --help" << "Display usage information and exit." << std::endl;
  std::cout << "Example:" << std::endl;
  std::cout << "  " << basename(name) << " log.txt 1:27 -11:01 +2:15:23 127" << std::endl;
}

void printVersion() {
  std::cout << "timetrack " VERSION << std::endl;
}

int main(int argc, char **argv) {
  // if no argument supplied, exit here
  if (argc <= 1) {
    printUsage(argv[0]);

    return 0;
  }

  // parse first argument
  if (argc >= 2) {
    std::string firstArgument = std::string(argv[1]);

    // check if version
    if (firstArgument == "--version") {
      printVersion();

      return 0;
    }

    // check if help
    if (firstArgument == "--help") {
      printUsage(argv[0]);

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

  // loop through the operands and add them to the total, and difference
  Time result(current.getTime()); // todo: copy constructor
  Time difference;

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

  // write to file
  bool writeSuccessful = putTime(argv[1], result, difference);

  if (writeSuccessful) {
    std::cout << "Wrote to '" << argv[1] << "'." << std::endl;
    return 0;
  } else {
    std::cout << "Couldn't write to '" << argv[1] << "'." << std::endl;
    return 1;
  }
}
