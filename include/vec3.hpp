#ifndef VEC3_HPP
#define VEC3_HPP

#include "util.hpp"

#include <cmath>
#include <ostream>

class vec3
{
public:
    // ============= Constructors =============
    constexpr vec3() noexcept = default;
    constexpr vec3(double e0, double e1, double e2) noexcept : e{ e0, e1, e2 }
    {
    }

    // ============= Getters =============
    [[nodiscard]] constexpr double x() const noexcept
    {
        return e[0];
    }
    [[nodiscard]] constexpr double y() const noexcept
    {
        return e[1];
    }
    [[nodiscard]] constexpr double z() const noexcept
    {
        return e[2];
    }

    // ============= Operator overloads =============
    [[nodiscard]] constexpr vec3 operator-() const noexcept
    {
        return vec3(-e[0], -e[1], -e[2]);
    }
    [[nodiscard]] constexpr double operator[](int i) const noexcept
    {
        return e[i];
    }
    constexpr double& operator[](int i) noexcept
    {
        return e[i];
    };

    constexpr vec3& operator+=(vec3 const& v) noexcept
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    constexpr vec3& operator*=(double t) noexcept
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    constexpr vec3& operator/=(double t) noexcept
    {
        return *this *= static_cast<double>(1 / t);
    }

    // ============= Member functions =============
    [[nodiscard]] double length() const noexcept // Note: std::sqrt can only be computed at runtime (as of cpp23)
    {
        return static_cast<double>(std::sqrt(length_squared()));
    }

    [[nodiscard]] constexpr double length_squared() const noexcept
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    [[nodiscard]] static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    [[nodiscard]] static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    [[nodiscard]] bool near_zero() const
    {
        // Return true if the vector is close to zero in all dimensions.
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

private:
    double e[3]{ 0, 0, 0 };
};

using point3 = vec3;

#endif // VEC3_HPP