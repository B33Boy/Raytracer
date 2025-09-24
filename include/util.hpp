#ifndef UTIL_HPP
#define UTIL_HPP

#include <limits> // numeric_limits

// ============= Constants =============
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// ============= Utility Functions =============
[[nodiscard]] inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

#include "interval.hpp"

#endif // UTIL_HPP