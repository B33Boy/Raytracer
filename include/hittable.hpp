#ifndef HITTABLE_H
#define HITTABLE_H

#include "interval.hpp"
#include "ray.hpp"

/**
 * Bundles info for a ray intersecting a surface.
 */
class hit_record
{
public:
    point3 p;
    vec3 normal;
    double t; // represents where the hit occurs along the ray
    bool front_face;

    /**
     * By computing dot product of ray and the given outward normal vector, we can determine if the ray is inside or
     * outside the object.
     * If ray and normal face same dir, then ray is inside the object (dot prod is positive).
     * If ray and normal face opposite dirs, then ray is outside the object (dot prod is negative).
     */
    constexpr void set_face_normal(ray const& r, vec3 const& outward_normal) noexcept
    {
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
public:
    virtual ~hittable() = default;

    // Hit only counts if tmin < t < tmax.
    virtual bool hit(ray const& r, interval ray_t, hit_record& rec) const = 0;
};

#endif // HITTABLE_HPP