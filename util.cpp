#include <string>
#include <stdlib.h>

std::string leftPad(int num) {
  return std::string(num < 10 ? "0" : "") + std::to_string(num);
}

std::string plural(int num, std::string singularForm, std::string pluralForm) {
  if (abs(num) == 1) {
    return std::to_string(num) + " " + singularForm;
  }

  return std::to_string(num) + " " + pluralForm;
}