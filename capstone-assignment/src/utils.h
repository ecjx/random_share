#ifndef EDWIN_UTILS_H
#define EDWIN_UTILS_H

#include <ctime>
#include <string_view>
#include <cmath>

namespace edwin_utils
{

int days_between(const std::tm& from, const std::tm& to);
std::tm parse_date(std::string_view date);

// there are better ways to do this like std::stod, but i dont want to enable RTTI to handle try-catch-throw, it is slow
template <typename T>
concept FloatType = std::is_floating_point_v<T>;

template <FloatType T>
T string_to(const std::string_view s, bool& success) 
{
    T result = static_cast<T>(0);
    success = true;
    bool negative = false;
    int i = 0;
    int len = s.size();

    if (s[i] == '-') {
        negative = true;
        i++;
    }

    bool decimal_found = false;
    int decimal_places = 0;

    for (; i < len; i++) 
    {
        if (s[i] == '.') 
        {
            if (decimal_found) 
            {
                success = false;
                return static_cast<T>(0); // Multiple decimals, invalid number
            }
            decimal_found = true;
            continue;
        }
        if (s[i] < '0' || s[i] > '9')
        {
            success = false;
            return static_cast<T>(0); // Non-numeric character
        }
        
        result *= 10;
        result += (s[i] - '0');

        if (decimal_found) 
            decimal_places++;
    }

    result /= std::pow(10, decimal_places);

    if (negative) result = -result;

    return result;
}

} //namespace edwin_utils


#endif // EDWIN_UTILS_H