#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <algorithm> // std::clamp
#include <cmath>     // std::round
#include <ostream>

using color = vec3;

constexpr inline double linear_to_gamma(double linear_component)
{
    if ( linear_component > 0 )
        return std::sqrt(linear_component);

    return 0;
}

void write_color(std::ostream& out, color const& pixel_color)
{
    // Apply a linear to gamma transform for gamma 2
    auto r = linear_to_gamma(pixel_color.x());
    auto g = linear_to_gamma(pixel_color.y());
    auto b = linear_to_gamma(pixel_color.z());

    // rgb values should be within [0, 1]
    r = std::clamp(r, 0.0, 1.0);
    g = std::clamp(g, 0.0, 1.0);
    b = std::clamp(b, 0.0, 1.0);

    // convert to the range [0, 255]
    int rbyte = static_cast<int>(std::round(255 * r));
    int gbyte = static_cast<int>(std::round(255 * g));
    int bbyte = static_cast<int>(std::round(255 * b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif // COLOR_HPP