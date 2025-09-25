#ifndef COLOR_HPP
#define COLOR_HPP

#include "interval.hpp"
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

    // Translate the [0,1] component values to the byte range [0,255].
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif // COLOR_HPP