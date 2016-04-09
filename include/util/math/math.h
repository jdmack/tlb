#ifndef TLB_MATH_H_
#define TLB_MATH_H_

#include "math.h"
#include "point.h"

namespace Math
{
    Point convert_to_isometric(Point point);
    Point convert_to_cartesian(Point point);
}

#endif
