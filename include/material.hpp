#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.hpp"
#include "hittable.hpp"

class material
{
public:
    virtual ~material() = default;

    virtual bool scatter(ray const& r_in, hit_record const& rec, color& attenuation, ray& scattered) const
    {
        return false;
    }
};

#endif