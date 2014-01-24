#include <cmath>
#include "movement.h"
#include "point.h"
#include "game_object.h"
#include "utils/logger.h"

Movement::Movement(Vector vector, Point start, Point destination)
{
    vector_ = vector;
    start_ = start;
    destination_ = destination;
    clockwise_ = false;
    degrees_ = 0;
}
