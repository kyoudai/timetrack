#include "time.h"
#include "io.h"
#include <iostream>
#include <iomanip>

int main(int argc, char **argv) {
  // if no argument supplied, exit here
  if (argc <= 1) {
    std::cout << "Usage: " << argv[0] << " file [time1 ...]" << std::endl;

    return 0;
  }

  Time current = getTime(argv[1]);

  std::cout << std::endl;
  std::cout << std::setw(10) << current << std::endl;

  if (argc <= 2) {
    return 0;
  }

  char operation = 43;
  Time result(current.getTime()); // todo: copy constructor

  for(int i = 2; i < argc; i++) {
    Time operand = Time(argv[i]);
    result = result + operand;

    std::cout << std::setw(10) << operation + operand.toString() << std::endl;
  }

  std::string separator = std::string(8, (char)196);

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
