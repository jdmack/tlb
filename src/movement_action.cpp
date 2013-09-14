#include <cmath>
#include "movement.h"
#include "coordinate.h"
#include "game_object.h"
#include "utils/logger.h"

Movement::Movement()
{
    distance_ = 0;
    clockwise_ = false;
    degrees_ = 0;
}

Movement::Movement(Vector vector)
{
    vector_ = vector;
    distance_ = 0;
    clockwise_ = false;
    degrees_ = 0;
}

Movement::Movement(double magnitude, double direction)
{
    vector_ = Vector(magnitude, direction);
    distance_ = 0;
    clockwise_ = false;
    degrees_ = 0;
}

Movement::Movement(Vector vector, Coordinate destination)
{
    vector_ = vector;
    destination_ = destination;
    distance_ = 0;
    clockwise_ = false;
    degrees_ = 0;
}

double Movement::calculate_distance(Coordinate point1, Coordinate point2)
{
    double x = point2.x_position() - point1.x_position();
    double y = point2.y_position() - point1.y_position();

    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}
