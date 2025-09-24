#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "hittable.hpp"

#include <memory>
#include <vector>

class hittable_list : public hittable
{
public:
    // ============= Constructors =============
    hittable_list() = default;

    hittable_list(std::shared_ptr<hittable> const& obj)
    {
        add(obj);
    }

    // ============= Member functions =============
    void add(std::shared_ptr<hittable> const& obj) noexcept
    {
        objects.push_back(obj);
    }

    bool hit(ray const& r, double ray_tmin, double ray_tmax, hit_record& rec) const override
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for ( auto const& obj : objects )
        {
            if ( obj->hit(r, ray_tmin, closest_so_far, temp_rec) )
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }

private:
    std::vector<std::shared_ptr<hittable>> objects;
};

#endif