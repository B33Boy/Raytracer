#include <iostream>
#include "raytracer.hpp"

color ray_color(ray const &r)
{
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    // ====== Image ======
    // Calculate image height
    constexpr auto aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 400;
    constexpr int image_height = std::max(1, static_cast<int>(image_width / aspect_ratio));

    // ====== Camera ======
    constexpr auto focal_length = 1.0;
    constexpr auto viewport_height = 2.0;
    constexpr auto viewport_width = viewport_height * static_cast<double>(image_width / image_height);
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

            auto pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}