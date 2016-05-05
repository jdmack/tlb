#ifndef TLB_MATH_H_
#define TLB_MATH_H_

#include "Math.h"
#include "Point.h"


#define toRadian(x) (float)(((x) * M_PI / 180.0f))
#define toDegree(x) (float)(((x) * 180.0f / M_PI))

namespace Math
{
    Point convertToIsometric(Point point);
    Point convertToCartesian(Point point);
}

#endif
