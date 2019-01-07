#include "time.h"
#include "util.h"
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

std::string Time::toTimeString() const {
  return leftPad(getHours()) + ":" + leftPad(getMinutes()) + ":" + leftPad(getSeconds());
}

std::string Time::toString() const {
  return std::string(seconds_ < 0 ? "-" : "") + toTimeString();
}

std::string Time::toSignedString() const {
  std::string sign("+");  

  if (seconds_ < 0) {
    sign = "-";
  }

  return sign + toTimeString();
}

std::string Time::toHumanString() const {
  const unsigned char hasHours = getHours() != 0 ? 0b00000100 : 0;
  const unsigned char hasMinutes = getMinutes() != 0 ? 0b00000010 : 0;
  const unsigned char hasSeconds = getSeconds() != 0 ? 0b00000001 : 0;

  const std::string negative = getTime() < 0 ? "negative " : "";

  // for now, it's easier to print a different text for each combination, rather than wrestle grammar
  switch(hasHours | hasMinutes | hasSeconds) {
    // nothing
    case 0b00000000:
      return "The current total is zero.";
    // only seconds
    case 0b00000001:
      return "The current total is " + negative + plural(getSeconds(), "second", "seconds") + ".";
    // only minutes
    case 0b00000010:
      return "The current total is exactly " + negative + plural(getMinutes(), "minute", "minutes") + ".";
    // only hours
    case 0b00000100:
      return "The current total is exactly " + negative + plural(getHours(), "hour", "hours") + ".";
    // minutes and seconds
    case 0b00000011:
      return "The current total is " + negative + plural(getMinutes(), "minute", "minutes") + " and "+ plural(getSeconds(), "second", "seconds") + ".";
    // hours and seconds
    case 0b00000101:
      return "The current total is " + negative + plural(getHours(), "hour", "hours") + " and "+ plural(getSeconds(), "second", "seconds") + ".";
    // hours and minutes
    case 0b00000110:
      return "The current total is " + negative + plural(getHours(), "hour", "hours") + " and "+ plural(getMinutes(), "minute", "minutes") + ".";
    // hours, minutes and seconds
    case 0b00000111:
      return "The current total is "
        + plural(getHours(), "hour", "hours") + ", "
        + plural(getMinutes(), "minute", "minutes") + ", and "
        + plural(getSeconds(), "second", "seconds")
        + ".";
    default:
      return "The current total is zero.";
  }
}
