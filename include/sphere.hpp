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

    [[nodiscard]] bool hit(ray const& r, interval ray_t, hit_record& rec) const override
    {
        auto const O_C = center - r.origin();
        auto const a = r.direction().length_squared();
        auto const h = dot(r.direction(), O_C);
        auto const c = O_C.length_squared() - radius * radius;

        // if discriminant == 0 then 1 root, if discriminant > 0 then 2 real roots
        // we dgaf about imaginary solutions
        auto discriminant = h * h - a * c;
        if ( discriminant < 0 )
            return false;

        // Find the nearest root that lies in the acceptable range.
        auto const sqrtd = std::sqrt(discriminant);
        auto root = (h - sqrtd) / a;

        if ( !ray_t.surrounds(root) )
        {
            root = (h + sqrtd) / a;
            if ( !ray_t.surrounds(root) )
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

#endif // SPHERE_HPP