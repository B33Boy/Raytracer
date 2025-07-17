#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"
#include "util.hpp"

class ray
{
public:
    // ============= Constructors =============
    constexpr ray() noexcept = default;
    constexpr ray(point3 const &origin, vec3 const &dir) noexcept : origin_(origin), dir_(dir) {}

    // ============= Getters =============
    [[nodiscard]] constexpr point3 const &origin() const noexcept { return origin_; }
    [[nodiscard]] constexpr vec3 const &direction() const noexcept { return dir_; }

    // ============= Member functions =============
    [[nodiscard]] constexpr point3 at(double t) const noexcept
    {
        return origin_ + t * dir_;
    }

private:
    point3 origin_{};
    vec3 dir_{};
};

#endif // RAY_HPP