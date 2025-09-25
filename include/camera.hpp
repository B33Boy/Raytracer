#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "hittable.hpp"
#include "interval.hpp"
#include "util.hpp"

#include <iostream>

struct cam_params
{
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 100; // Count of random samples for each pixel
};

struct derived_params
{
    double pixel_samples_scale; // Color scale factor for a sum of pixel samples
    point3 center;
    int image_height;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    point3 pixel00_loc;
};

// Free function defined before constructor
constexpr derived_params compute_derived_params(cam_params const& p)
{
    // ====== Image ======
    double pixel_samples_scale = 1.0 / p.samples_per_pixel;

    int image_height = static_cast<int>(p.image_width / p.aspect_ratio);
    image_height = (image_height > 1) ? image_height : 1;

    point3 center{ 0, 0, 0 };

    // ====== Camera ======
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * static_cast<double>(p.image_width) / image_height;

    // // ====== Calculate vectors across horizontal and down vertical viewport edge ======
    auto viewport_u = vec3(viewport_width, 0, 0);   // >
    auto viewport_v = vec3(0, -viewport_height, 0); // v

    // ====== Calculate horizontal and vertical delta vectors ======
    auto pixel_delta_u = viewport_u / p.image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // ====== Calculate the location of upper left pixel ======
    auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left +
                       0.5 * (pixel_delta_u + pixel_delta_v); // we do 0.5 to move to the center of the first pixel

    return derived_params{ pixel_samples_scale, center, image_height, pixel_delta_u, pixel_delta_v, pixel00_loc };
}

class camera
{
public:
    constexpr explicit camera(cam_params const& params) : p(params), d{ compute_derived_params(p) }
    {
    }

    void render(hittable const& world) const
    {
        std::cout << "P3\n" << p.image_width << ' ' << d.image_height << "\n255\n";

        for ( int j = 0; j < d.image_height; j++ )
        {
            std::clog << "\rScanlines remaining: " << (d.image_height - j) << ' ' << std::flush;
            for ( int i = 0; i < p.image_width; i++ )
            {
                color pixel_color(0, 0, 0);
                for ( int sample = 0; sample < p.samples_per_pixel; sample++ )
                {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }
                write_color(std::cout, d.pixel_samples_scale * pixel_color);
            }
        }

        std::clog << CURSOR_START << CLEAR_LINE << "Done.";
    }

private:
    cam_params const p;     // contains configurable params
    derived_params const d; // contains the derived params

    color ray_color(ray const& r, hittable const& world) const
    {
        hit_record rec;

        if ( world.hit(r, interval(0, infinity), rec) )
        {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * COLOR_WHITE + a * COLOR_LIGHT_BLUE;
    }

    ray get_ray(int i, int j) const
    {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = d.pixel00_loc + ((i + offset.x()) * d.pixel_delta_u) + ((j + offset.y()) * d.pixel_delta_v);

        auto ray_origin = d.center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const
    {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
};

#endif // CAMERA_HPP