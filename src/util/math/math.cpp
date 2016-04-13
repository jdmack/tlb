#include "util/math/math.h"
#include "point.h"

Point Math::convertToIsometric(Point point)
{
    //float x = point.x() - point.y();
    //float y = (point.x() + point.y()) / 2;
    float x = point.x();
    float y = point.y();// / 2;
    return Point(x, y);
}
Point Math::convertToCartesian(Point point)
{
    //float x = (2 * point.y() + point.x()) / 2;
    //float y = (2 * point.y() - point.x()) / 2;
    float x = point.x();
    float y = point.y();// * 2;

    return Point(x, y);
}


