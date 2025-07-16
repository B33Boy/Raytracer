#ifndef UTIL_HPP
#define UTIL_HPP

#include "vec3.hpp"

// ============= Vec3 utility functions =============
inline std::ostream &operator<<(std::ostream &out, vec3 const &v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

[[nodiscard]] constexpr inline vec3 operator+(const vec3 &u, const vec3 &v) noexcept
{
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

[[nodiscard]] constexpr inline vec3 operator-(const vec3 &u, const vec3 &v) noexcept
{
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

[[nodiscard]] constexpr inline vec3 operator*(const vec3 &u, const vec3 &v) noexcept
{
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

[[nodiscard]] constexpr inline vec3 operator*(double t, const vec3 &v) noexcept
{
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

[[nodiscard]] constexpr inline vec3 operator*(const vec3 &v, double t) noexcept
{
    return t * v;
}

[[nodiscard]] constexpr inline vec3 operator/(const vec3 &v, double t) noexcept
{
    return (1 / t) * v;
}

[[nodiscard]] constexpr inline double dot(const vec3 &u, const vec3 &v) noexcept
{
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

[[nodiscard]] constexpr inline vec3 cross(const vec3 &u, const vec3 &v) noexcept
{
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

[[nodiscard]] constexpr inline vec3 unit_vector(const vec3 &v) noexcept
{
    if (v.length() == 0.0)
        return vec3(0, 0, 0);

    return v / v.length();
}

#endif