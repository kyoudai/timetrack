#include "io.h"
#include "time.h"
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctype.h>

bool isValidEntry(std::string const& entry) {
  if(entry.empty()) {
    return false;
  }

  char first = entry.at(0);

  return std::isdigit(first) || first == '-';
}

Time getTime(std::string file) {
  std::ifstream in(file);

  if (in.is_open()) {
    std::string line;
    std::string last;

    while (std::getline(in, line)) {
      // ignore line if it doesn't start with a digit
      if (isValidEntry(line)) {
        last = line;
      }
    }

    in.close();

    if (last.empty()) {
      Time zero;
      return zero;
    } else {
      return Time(last.substr(0, last.find(',')));
    }
  }

  std::cout << "Can't open '" << file << "' for reading." << std::endl;
  std::exit(1);
}

bool putTime(std::string file, Time time, Time changed) {
  std::ofstream out;

  auto now = std::time(nullptr);
  auto tm = *std::localtime(&now);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
  std::string pretty = oss.str();

  out.open(file, std::ios::out | std::ios::app);

  // read the last character in the file
  std::ifstream in(file, std::ios::ate);
  in.seekg(-1, std::ios_base::end);
  char lastChar;
  in.get(lastChar);
  in.close();

  if (out.is_open()) {
    // insert newline if needed
    if (lastChar != '\n' && lastChar != 0) {
      out << std::endl;
    }

    out << time << "," << changed << "," << pretty << std::endl;
    out.close();

    return true;
  }

  return false;
}
