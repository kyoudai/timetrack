#include "time.h"
#include "io.h"
#include <iostream>
#include <iomanip>
#include <vector>

std::string basename(std::string const& path) {
  return path.substr(path.find_last_of("/\\") + 1);
}

void printUsage(std::string const& name) {
  std::cout << "Usage: " << basename(name) << " [options] file [options] [time1 time2 ...]" << std::endl;
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

  bool OPT_VERBOSE = false;

  std::string filePath; // consumed by the first non-flag argument
  std::vector<std::string> operands;

  // loop through the arguments
  for(int i = 1; i < argc; i++) {
    const std::string argument = std::string(argv[i]);
    
    // check if version
    if (argument == "--version") {
      printVersion();

      return 0;
    }

    // check if help
    if (argument == "--help") {
      printUsage(argv[0]);

      return 0;
    }

    // check for verbose
    if (argument == "-v") {
      OPT_VERBOSE = true;

      continue;
    }

    if (filePath.empty()) {
      filePath = argument;

      continue;
    }

    // finally, treat it as an operand
    operands.push_back(argument);
  }

  // read current time
  // this exits immediately if file can't be accessed
  Time current = getTime(filePath); 

  // if no operands, print current time and exit
  if (operands.empty()) {
    std::cout << std::endl;
    std::cout << std::setw(10) << current << std::endl;

    return 0;
  }

  // loop through the operands and add them to the total, and difference
  Time result(current.getTime()); // todo: copy constructor
  Time difference;

  // print the current time
  std::cout << std::endl;
  std::cout << std::setw(10) << current << std::endl;

  // go through the rest of the entries
  for (auto const& value: operands) {
    Time operand = Time(value);

    result = result + operand;
    difference = difference + operand;

    std::cout << std::setw(10) << operand.toSignedString() << std::endl;
  }

  // print the summary
  std::string separator = std::string(8, '-');

  std::cout << std::setw(10) << separator << std::endl;
  std::cout << std::setw(10) << result << std::endl;
  std::cout << std::endl;

  // write to file
  bool writeSuccessful = putTime(filePath, result, difference);

  if (writeSuccessful) {
    std::cout << "Wrote to '" << filePath << "'." << std::endl;
    return 0;
  } else {
    std::cout << "Couldn't write to '" << filePath << "'." << std::endl;
    return 1;
  }
}
