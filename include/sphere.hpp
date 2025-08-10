#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable
{
public:
    constexpr sphere(point3 const& center, double radius) : center(center), radius(std::fmax(0, radius))
    {
    }

    [[nodiscard]] bool hit(ray const& r, double ray_tmin, double ray_tmax, hit_record& rec) const override
    {
        auto const O_C = center - r.origin();
        auto const a = r.direction().length_squared();
        auto const h = dot(r.direction(), O_C);
        auto const c = O_C.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;
        // if discriminant == 0 then 1 root, if discriminant > 0 then 2 real roots
        // we dgaf about imaginary solutions

        if ( discriminant < 0 )
            return false;

        auto const sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if ( root <= ray_tmin || ray_tmax <= root )
        {
            root = (h + sqrtd) / a;
            if ( root <= ray_tmin || ray_tmax <= root )
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};

#endif