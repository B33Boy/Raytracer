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

    bool hit(ray const& r, interval ray_t, hit_record& rec) const override
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for ( auto const& obj : objects )
        {
            if ( obj->hit(r, interval(ray_t.min, closest_so_far), temp_rec) )
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

#endif // HITTABLE_LIST_HPP