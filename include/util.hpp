#ifndef UTIL_HPP
#define UTIL_HPP

#include <limits> // numeric_limits

// ============= Macros =============
#define CURSOR_START "\r"   // Carriage return to go back to beginning of a line of text
#define CLEAR_LINE "\033[K" // ANSI escape code to clear from cursor to end of line

#define COLOR_WHITE color(1.0, 1.0, 1.0)
#define COLOR_LIGHT_BLUE color(0.5, 0.7, 1.0)

// ============= Constants =============
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// ============= Utility Functions =============
[[nodiscard]] inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

#endif // UTIL_HPP