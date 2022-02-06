#pragma once

#include "Point.h"

namespace EA
{
template <typename T>
struct Rect
{
    Rect() = default;

    Rect(const Rect&) = default;

    Rect(T xToUse, T yToUse, T width, T height) noexcept
        : x(xToUse)
        , y(yToUse)
        , w(width)
        , h(height)
    {
    }

    Rect(T width, T height) noexcept
        : w(width)
        , h(height)
    {
    }

    Rect(Point<T> corner1, Point<T> corner2) noexcept
        : x(std::min(corner1.x, corner2.x))
        , y(std::min(corner1.y, corner2.y))
        , w(corner1.x - corner2.x)
        , h(corner1.y - corner2.y)
    {
        if (w < T())
            w = -w;
        if (h < T())
            h = -h;
    }

    Point<T> getPos() { return {x, y}; }

    T x {}, y {};
    T w {}, h {};
};

} // namespace EA