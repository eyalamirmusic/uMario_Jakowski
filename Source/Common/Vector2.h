#pragma once

class Vector2
{
public:
    Vector2() = default;
    Vector2(int xToUse, int yToUse);

    int getX() const;
    void setX(int xToUse);

    int getY() const;
    void setY(int yToUse);

private:
    int x = 0;
    int y = 0;
};