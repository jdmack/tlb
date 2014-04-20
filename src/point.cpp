#include <cstdint>
#include <sstream>
#include "point.h"
#include "constants.h"
#include "screen.h"

Point::Point()
{
	// Default location is center of screen
    x_= kScreenWidth / 2;
    y_= kScreenHeight / 2;
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
