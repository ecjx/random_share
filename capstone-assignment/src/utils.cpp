#include "utils.h"

namespace edwin_utils
{

int days_between(const std::tm& from, const std::tm& to)
{
    std::tm from_copy = from;
    std::tm to_copy = to;
    std::time_t from_time = std::mktime(&from_copy);
    std::time_t to_time = std::mktime(&to_copy);
    return std::difftime(to_time, from_time) / (60 * 60 * 24);
}

int sv_to_int(std::string_view sv, bool &success) 
{
    int value = 0;
    bool is_negative = false;
    success = true;

    size_t start = 0;
    if (sv[0] == '-') {
        is_negative = true;
        start = 1;
    }

    for (size_t i = start; i < sv.size(); i++) {
        char ch = sv[i];
        if (ch < '0' || ch > '9') {
            success = false;
            return 0;
        }
        value = value * 10 + (ch - '0');
    }

    return is_negative ? -value : value;
}


std::tm parse_date(std::string_view date)
{
    std::tm result = {};

    if (date.size() != 10) 
        return result; // Invalid length for "YYYY-MM-DD"
    
    if(date[4] != '-' || date[7] != '-')
        return result; // Invalid format (missing dashes

    bool success = true;
    result.tm_year = sv_to_int(date.substr(0, 4), success) - 1900; // since 1900
    if(!success)
        return {}; // Invalid year
    result.tm_mon  = sv_to_int(date.substr(5, 2), success) - 1;    // 0-indexed
    if(!success)
        return {}; // Invalid month
    result.tm_mday = sv_to_int(date.substr(8, 2), success);        // Day of the month
    if(!success)
        return {}; // Invalid day

    return result;
}

} // namespace edwin_utils

