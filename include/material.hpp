#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.hpp"
#include "hit_record.hpp"
#include "ray.hpp"

class material
{
public:
    virtual ~material() = default;

    virtual bool scatter(ray const& r_in, hit_record const& rec, color& attenuation, ray& scattered) const = 0;
};

class metal : public material
{
public:
    metal(color const& albedo) : albedo(albedo)
    {
    }

    bool scatter(ray const& r_in, hit_record const& rec, color& attenuation, ray& scattered) const override
    {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

class lambertian : public material
{
public:
    lambertian(color const& albedo) : albedo(albedo)
    {
    }

    bool scatter(ray const& r_in, hit_record const& rec, color& attenuation, ray& scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if ( scatter_direction.near_zero() )
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

#endif