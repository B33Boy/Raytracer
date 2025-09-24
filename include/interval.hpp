#ifndef INTERVAL_HPP
#define INTERVAL_HPP

class interval
{
public:
    double min, max; // keep public, simple class

    // ============= Constructors =============
    constexpr interval() : min(+infinity), max(-infinity)
    {
    } // Default interval is empty

    constexpr interval(double min, double max) : min(min), max(max)
    {
    }

    // ============= Member functions =============
    [[nodiscard]] constexpr double size() const noexcept
    {
        return max - min;
    }

    [[nodiscard]] constexpr bool contains(double x) const noexcept
    {
        return min <= x && x <= max;
    }

    [[nodiscard]] constexpr bool surrounds(double x) const noexcept
    {
        return min < x && x < max;
    }

    static const interval empty;
    static const interval universe;
};

inline const interval interval::empty = interval(+infinity, -infinity);
inline const interval interval::universe = interval(-infinity, +infinity);

#endif // INTERVAL_HPP