
#include <sstream>
#include <cmath>
#include "math/Vector2f.h"

Vector2f::Vector2f()
{
	// Default location is center of renderer
    x_= 0;
    y_= 0;
}

Vector2f::Vector2f(float x, float y)
{
    x_= x;
    y_= y;
}

std::string Vector2f::toString()
{
    std::stringstream ss;
    ss << "(" << x_ << "," << y_ << ")";
    return ss.str();
}

Vector2f & Vector2f::operator=(Vector2f v)
{
    x_ = v.x();
    y_ = v.y();
    return *this;
}

bool Vector2f::operator==(const Vector2f &other) const
{
    if((x_ == other.x()) && (y_ == other.y())) {
        return true;
    }
    else {
        return false;
    }
}

bool Vector2f::operator!=(const Vector2f &other) const
{
    return !(*this == other);
}

float Vector2f::distanceFrom(Vector2f point)
{
    float xDistance = point.x() - x_;
    float yDistance = point.y() - y_;
    return sqrt((xDistance * xDistance) + (yDistance * yDistance));
}

std::ostream & operator<<(std::ostream & os, const Vector2f & v)
{
        os << "(" << v.x() << ", " << v.y() << ">";
        return os;
}
