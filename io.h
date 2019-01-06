#ifndef IO_H
#define IO_H

#include <string>
#include "time.h"

Time getTime(std::string file);
bool putTime(std::string file, Time time, Time changed);
std::string getTimeNowIso();
char getLastChar(std::string file);

#endif

