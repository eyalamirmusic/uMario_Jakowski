#include "Vector2.h"

Vector2::Vector2(int xToUse, int yToUse)
{
    x = xToUse;
    y = yToUse;
}

int Vector2::getX() const
{
    return x;
}

void Vector2::setX(int xToUse)
{
    x = xToUse;
}

int Vector2::getY() const
{
    return y;
}

void Vector2::setY(int yToUse)
{
    y = yToUse;
}