#pragma once

#include <algorithm>
#include <cmath>

namespace EA
{
namespace Math
{
template <typename T>
constexpr T limit(T min, T max, T value)
{
    auto maxLimited = std::min(value, max);
    auto minLimited = std::max(maxLimited, min);

    return minLimited;
}
} // namespace Math

template <typename T>
struct Point
{
    constexpr Point() = default;
    constexpr Point(const Point&) = default;

    constexpr Point(T xToUse, T yToUse) noexcept
        : x(xToUse)
        , y(yToUse)
    {
    }

    Point& operator=(const Point&) = default;

    constexpr inline bool operator==(Point other) const noexcept
    {
        return x == other.x && y == other.y;
    }
    constexpr inline bool operator!=(Point other) const noexcept
    {
        return x != other.x || y != other.y;
    }

    constexpr Point withX(T newX) const noexcept { return {newX, y}; }
    constexpr Point withY(T newY) const noexcept { return {x, newY}; }

    constexpr Point translated(T deltaX, T deltaY) const noexcept
    {
        return {x + deltaX, y + deltaY};
    }

    constexpr Point operator+(const Point& other) const noexcept
    {
        return {x + other.x, y + other.y};
    }

    Point& operator+=(const Point& other) noexcept
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    constexpr Point operator-(const Point& other) const noexcept
    {
        return Point(x - other.x, y - other.y);
    }

    Point& operator-=(const Point& other) noexcept
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    constexpr Point operator-() const noexcept { return Point(-x, -y); }

    T x {};
    T y {};
};

} // namespace EA