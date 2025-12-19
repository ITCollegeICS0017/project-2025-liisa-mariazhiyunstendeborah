#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

#include <string>
#include <sstream>
#include <chrono>
#include <stdexcept>

#include "utilities/constantdefs.h"

namespace CustomFuncs {
    Service ServicefromInt (int enumval);

    CompletionStatus ComplStatusfromInt (int enumval);

    std::chrono::year_month_day DatefromStringStream (std::string str);

    std::string DatetoString (std::chrono::year_month_day ymd);
}

#endif