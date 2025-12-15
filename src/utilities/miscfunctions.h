#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

#include <chrono>

#include "utilities/constantdefs.h"

Service ServicefromInt (int enumval);

std::chrono::year_month_day DatefromStringStream (std::string str);

#endif