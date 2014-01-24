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
    std::ostringstream convert;
    return static_cast<std::ostringstream*>( &(std::ostringstream() << "(" << x_ << "," << y_ << ")") )->str();
}
