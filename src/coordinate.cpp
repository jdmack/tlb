#include <cstdint>
#include "coordinate.h"
#include "constants.h"
#include "screen.h"

Coordinate::Coordinate()
{
    x_position_ = kScreenWidth / 2;
    y_position_ = kScreenHeight / 2;
}

Coordinate::Coordinate(double x, double y)
{
    x_position_ = x;
    y_position_ = y;
}
