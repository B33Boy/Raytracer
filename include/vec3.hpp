#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <ostream>

class vec3
{
public:
    // ============= Constructors =============
    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // ============= Getters =============
    [[nodiscard]] constexpr double x() const noexcept { return e[0]; }
    [[nodiscard]] constexpr double y() const noexcept { return e[1]; }
    [[nodiscard]] constexpr double z() const noexcept { return e[2]; }

    // ============= Operator overloads =============
    [[nodiscard]] constexpr vec3 operator-() const noexcept { return vec3(-e[0], -e[1], -e[2]); }
    [[nodiscard]] constexpr double operator[](int i) const noexcept { return e[i]; }
    constexpr double &operator[](int i) noexcept { return e[i]; };

    constexpr vec3 &operator+=(vec3 const &v) noexcept
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    constexpr vec3 &operator*=(double t) noexcept
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    constexpr vec3 &operator/=(double t) noexcept
    {
        return *this *= static_cast<double>(1 / t);
    }

    // ============= Member functions =============
    [[nodiscard]] constexpr double length() const noexcept
    {
        return static_cast<double>(std::sqrt(length_squared()));
    }

    [[nodiscard]] constexpr double length_squared() const noexcept
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

private:
    double e[3];
};

using point3 = vec3;

// ============= Utility functions =============
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