
#include <sstream>
#include <cmath>
#include "point.h"

Point::Point()
{
	// Default location is center of renderer
    x_= 0;
    y_= 0;
}

Point::Point(double x, double y)
{
    x_= x;
    y_= y;
}

std::string Point::toString()
{
    std::stringstream ss;
    ss << "(" << x_ << "," << y_ << ")";
    return ss.str();
}

bool Point::operator==(const Point &other) const
{
    if((x_ == other.x()) && (y_ == other.y())) {
        return true;
    }
    else {
        return false;
    }
}

bool Point::operator!=(const Point &other) const
{
    return !(*this == other);
}

double Point::distanceFrom(Point point)
{
    double xDistance = point.x() - x_;
    double yDistance = point.y() - y_;
    return sqrt((xDistance * xDistance) + (yDistance * yDistance));
}
