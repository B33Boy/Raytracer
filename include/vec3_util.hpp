#ifndef VEC3_UTIL_HPP
#define VEC3_UTIL_HPP

#include "vec3.hpp"

// ============= Vec3 utility functions =============
inline std::ostream& operator<<(std::ostream& out, vec3 const& v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

[[nodiscard]] constexpr inline vec3 operator+(const vec3& u, const vec3& v) noexcept
{
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

[[nodiscard]] constexpr inline vec3 operator-(const vec3& u, const vec3& v) noexcept
{
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

[[nodiscard]] constexpr inline vec3 operator*(const vec3& u, const vec3& v) noexcept
{
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

[[nodiscard]] constexpr inline vec3 operator*(double t, const vec3& v) noexcept
{
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

[[nodiscard]] constexpr inline vec3 operator*(const vec3& v, double t) noexcept
{
    return t * v;
}

[[nodiscard]] constexpr inline vec3 operator/(const vec3& v, double t) noexcept
{
    return (1 / t) * v;
}

[[nodiscard]] constexpr inline double dot(const vec3& u, const vec3& v) noexcept
{
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

[[nodiscard]] constexpr inline vec3 cross(const vec3& u, const vec3& v) noexcept
{
    return vec3(u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(), u.x() * v.y() - u.y() * v.x());
}

[[nodiscard]] constexpr inline vec3 unit_vector(const vec3& v) noexcept
{
    if ( v.length() == 0.0 )
        return vec3(0, 0, 0);

    return v / v.length();
}

[[nodiscard]] inline vec3 random_unit_vector()
{
    /**
     * Rejection method to generate samples until we produce one that meets criteria.
     * 1. Generate random vec inside unit sphere
     * 2. Normalize to extend it to sphere surface
     * 3. Invert the normalized vector if it falls onto wrong hemisphere
     *
     * Note: because floating point numbers have finite precision, a small value can underflow to 0 when squared.
     *  This can cause the normalized vector to approach infinity, so we need a minimum size of points to reject.
     */
    while ( true )
    {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if ( lensq > 1e-160 && lensq <= 1 )
            return p / sqrt(lensq);
    }
}

[[nodiscard]] inline vec3 random_on_hemisphere(vec3 const& normal)
{
    /**
     * Using the normal, we can do dot product with the generated unit vector to ensure that it points in the same
     * hemisphere (i.e. unit vector and normal have acute angle).
     */

    vec3 on_unit_sphere = random_unit_vector();
    if ( dot(on_unit_sphere, normal) > 0.0 ) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

[[nodiscard]] inline vec3 reflect(vec3 const& v, vec3 const& n)
{
    return v - 2 * dot(v, n) * n;
}

#endif // VEC3_UTIL_HPP