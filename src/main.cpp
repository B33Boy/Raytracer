#include <iostream>

#include "raytracer.hpp"
#include "timer.hpp"

#define CURSOR_START "\r"
#define CLEAR_LINE "\033[K" // ANSI escape code to clear from cursor to end of line

#define COLOR_WHITE color(1.0, 1.0, 1.0)
#define COLOR_LIGHT_BLUE color(0.5, 0.7, 1.0)

[[nodiscard]] constexpr double hit_sphere(auto const &center, const double radius, ray const &r) noexcept
{

    auto const O_C = center - r.origin();
    auto const a = dot(r.direction(), r.direction());
    auto const b = -2.0 * dot(r.direction(), O_C);
    auto const c = dot(O_C, O_C) - radius * radius;
    auto const discriminant = b * b - 4 * a * c;

    // if discriminant == 0 then 1 root, if discriminant > 0 then 2 real roots
    // we dgaf about imaginary solutions

    if (discriminant < 0)
        return -1.0; // no hit
    else
        return (-b - std::sqrt(discriminant)) / (2.0 * a); // the smallest root of quadratic formula (closest intersection along the ray)
}

color ray_color(ray const &r)
{
    // Draw the point where the ray intersects the sphere
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);

    if (t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    // Draw the background
    vec3 unit_direction = unit_vector(r.direction());      //  [-1, 1]
    auto a = 0.5 * (unit_direction.y() + 1.0);             // scale it to [0, 1]
    return (1.0 - a) * COLOR_WHITE + a * COLOR_LIGHT_BLUE; // Blend between two colours
}

int main()
{
    scoped_timer timer;

    // ====== Image ======
    // Calculate image height
    constexpr auto aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 400;
    constexpr int image_height = std::max(1, static_cast<int>(image_width / aspect_ratio));

    // ====== Camera ======
    constexpr auto focal_length = 1.0;
    constexpr auto viewport_height = 2.0;
    constexpr auto viewport_width = viewport_height * static_cast<double>(image_width) / image_height;
    constexpr auto camera_center = point3(0, 0, 0);

    // ====== Calculate vectors across horizontal and down vertical viewport edge ======
    constexpr auto viewport_u = vec3(viewport_width, 0, 0);   // >
    constexpr auto viewport_v = vec3(0, -viewport_height, 0); // v

    // ====== Calculate horizontal and vertical delta vectors ======
    constexpr auto pixel_delta_u = viewport_u / image_width;
    constexpr auto pixel_delta_v = viewport_v / image_height;

    // ====== Calculate the location of upper left pixel ======
    constexpr auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    constexpr auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // we do 0.5 to move to the center of the first pixel

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << CURSOR_START << CLEAR_LINE << "Done.";
}
