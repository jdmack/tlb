
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

std::string Point::to_string()
{
    std::stringstream ss;
    ss << "(" << x_ << "," << y_ << ")";
    return ss.str();
}

bool Point::operator==(const Point &other) const {
    if((x_ == other.x()) && (y_ == other.y())) {
        return true;
    }
    else {
        return false;
    }
}
double Point::distance_from(Point point)
{
    double x_distance = point.x() - x_;
    double y_distance = point.y() - y_;
    return sqrt((x_distance * x_distance) + (y_distance * y_distance));
}
