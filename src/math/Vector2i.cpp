
#include <sstream>
#include <cmath>
#include "math/Vector2i.h"

Vector2i::Vector2i()
{
	// Default location is center of renderer
    x_= 0;
    y_= 0;
}

Vector2i::Vector2i(int x, int y)
{
    x_= x;
    y_= y;
}

std::string Vector2i::toString()
{
    std::stringstream ss;
    ss << "(" << x_ << "," << y_ << ")";
    return ss.str();
}

bool Vector2i::operator==(const Vector2i &other) const
{
    if((x_ == other.x()) && (y_ == other.y())) {
        return true;
    }
    else {
        return false;
    }
}

bool Vector2i::operator!=(const Vector2i &other) const
{
    return !(*this == other);
}

int Vector2i::distanceFrom(Vector2i point)
{
    int xDistance = point.x() - x_;
    int yDistance = point.y() - y_;
    return sqrt((xDistance * xDistance) + (yDistance * yDistance));
}
