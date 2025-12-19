#include "utilities/miscfunctions.h"


Service CustomFuncs::ServicefromInt (int enumval) {
    switch(enumval) {
        case 0: return Service::Photo_printing;
        case 1: return Service::Film_devel;
        default:
            throw std::invalid_argument("Not an enum!");
    }
    return Service::Invalid_Service;
}

CompletionStatus CustomFuncs::ComplStatusfromInt (int enumval) {
    switch(enumval) {
        case 0: return CompletionStatus::Created;
        case 1: return CompletionStatus::Assigned;
        case 2: return CompletionStatus::InProgress;
        case 3: return CompletionStatus::Completed;
        default:
            throw std::invalid_argument("Not an enum!");
    }
    return CompletionStatus::Invalid_Status;
}

std::chrono::year_month_day CustomFuncs::DatefromStringStream (std::string str) {
        std::tm tm = {};
        std::stringstream ss(str);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        std::time_t tt = std::mktime(&tm);
        auto tp = std::chrono::system_clock::from_time_t(tt);
        return std::chrono::floor<std::chrono::days>(tp);
        //IMPORTANT!!! add errorchecking
}

std::string CustomFuncs::DatetoString (std::chrono::year_month_day ymd) {
    std::ostringstream oss;
    oss << ymd;
    return oss.str();
}
