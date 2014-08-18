#include "utils/math.h"
#include "point.h"

Point Math::convert_to_isometric(Point point)
{
    double x = point.x() - point.y();
    double y = (point.x() + point.y()) / 2;

    return Point(x, y);
}
Point Math::convert_to_cartesian(Point point)
{
    double x = (2 * point.y() + point.x()) / 2;
    double y = (2 * point.y() - point.x()) / 2;

    return Point(x, y);
}


