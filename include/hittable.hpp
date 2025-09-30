#ifndef HITTABLE_H
#define HITTABLE_H

#include "hit_record.hpp"
#include "interval.hpp"
#include "ray.hpp"

#include <memory>

class hittable
{
public:
    virtual ~hittable() = default;

    // Hit only counts if tmin < t < tmax.
    virtual bool hit(ray const& r, interval ray_t, hit_record& rec) const = 0;
};

#endif // HITTABLE_HPP