#include <cmath>
#include "movement.h"
#include "point.h"
#include "game_object.h"
#include "utils/logger.h"

Movement::Movement(Vector vector, Point destination)
{
    vector_ = vector;
    destination_ = destination;
    distance_ = 0;
    clockwise_ = false;
    degrees_ = 0;
}

double Movement::calculate_distance(Point point1, Point point2)
{
    double x = point2.x() - point1.x();
    double y = point2.y() - point1.y();

    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}
