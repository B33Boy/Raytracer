#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include "ray.hpp"

#include <memory>

class material;

/**
 * Bundles info for a ray intersecting a surface.
 */
class hit_record
{
public:
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat;
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
#endif // HIT_RECORD_HPP