#include "time.h"
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <stdlib.h>

Time::Time(): seconds_(0) {}
Time::Time(int seconds): seconds_(seconds) {}

Time::Time(const std::string timestamp) {
  seconds_ = 0;
  char sign = 1;
  std::string uTimestamp = timestamp;

  if (timestamp.at(0) == '-') {
    sign = -1;
    uTimestamp = timestamp.substr(1); 
  }
  if (timestamp.at(0) == '+') {
    uTimestamp = timestamp.substr(1);
  }

  std::vector<int> time;
  std::stringstream stream(uTimestamp);
  std::string part;

  while(std::getline(stream, part, ':')) {
    time.insert(time.begin(), std::stoi(part));
  }

  if (time.size() > 0) { seconds_ += time.at(0); }
  if (time.size() > 1) { seconds_ += time.at(1) * 60; }
  if (time.size() > 2) { seconds_ += time.at(2) * 3600; }

  seconds_ *= sign;
}

Time Time::fromMinutes(int minutes) {
  return Time(minutes * 60);
}

int Time::getSeconds() const {
  return std::abs(seconds_ % 60);
}

int Time::getMinutes() const {
  return std::abs(seconds_ % 3600 / 60);
}

int Time::getHours() const {
  return std::abs(seconds_ / 3600);
}

int Time::getTime() const {
  return seconds_;
}

Time Time::operator+(const Time& b) {
  return Time(getTime() + b.getTime());
}

std::string Time::toString() const {
  return std::string(seconds_ < 0 ? "-" : "") + leftPad(getHours()) + ":" + leftPad(getMinutes()) + ":" + leftPad(getSeconds());
}

std::string Time::leftPad(int num) const {
  return std::string(num < 10 ? "0" : "") + std::to_string(num);
}
