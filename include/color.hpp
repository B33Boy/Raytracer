#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <algorithm> // std::clamp
#include <cmath>     // std::round
#include <ostream>

using color = vec3;

void write_color(std::ostream& out, color const& pixel_color)
{
    // rgb values should be within [0, 1]
    auto r = std::clamp(pixel_color.x(), 0.0, 1.0);
    auto g = std::clamp(pixel_color.y(), 0.0, 1.0);
    auto b = std::clamp(pixel_color.z(), 0.0, 1.0);

    // convert to the range [0, 255]
    int rbyte = static_cast<int>(std::round(255 * r));
    int gbyte = static_cast<int>(std::round(255 * g));
    int bbyte = static_cast<int>(std::round(255 * b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif // COLOR_HPP