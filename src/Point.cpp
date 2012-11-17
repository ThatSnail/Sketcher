#include "Point.h"

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::~Point()
{
    //dtor
}

bool Point::operator==(Point point)
{
    if(x == point.x && y == point.y)
    {
        return true;
    }
    return false;
}

bool Point::operator<(const Point& point) const
{
    if(y < point.y)
    {
        return true;
    }
    else if(y == point.y && x < point.x)
    {
        return true;
    }
    return false;
}
