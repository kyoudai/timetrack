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

#ifndef __MINGW32__
#include <mutex>
#endif

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

char getLastChar(std::string file) {
  std::ifstream in(file, std::ios::ate);
  in.seekg(-1, std::ios_base::end);
  char last;
  in.get(last);
  in.close();

  return last;
}

std::string getTimeNowIso() {
  auto now = std::time(nullptr);
  auto tm = *std::localtime(&now);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");

  return oss.str();
}

bool putTime(std::string file, Time time, Time changed) {
  #ifndef __MINGW32__
  static std::mutex mutex;
  std::lock_guard<std::mutex> lock(mutex);
  #endif

  std::ofstream out;
  out.open(file, std::ios::out | std::ios::app);

  if (!out.is_open()) {
    return false;
  }

  // insert newline if needed
  char lastChar = getLastChar(file);
  if ((int) lastChar != 10 && (int) lastChar != 0) {
    out << std::endl;
  }

  // write new entry
  out << time << "," << changed << "," << time.getTime() << "," << changed.getTime() << "," << getTimeNowIso() << std::endl;

  return true;
}
