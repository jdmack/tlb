#include <cmath>
#include <sstream>
#include <string>
#include "movement.h"
#include "point.h"
#include "game_object.h"
#include "util/logger.h"

Movement::Movement(Vector vector, Point start, Point destination)
{
    vector_ = vector;
    start_ = start;
    destination_ = destination;
    clockwise_ = false;
    degrees_ = 0;
}

std::string Movement::to_string()
{
    std::stringstream ss;
    ss << "Movement(Start:" << start_.to_string() << ", Destination:" << destination_.to_string() << ")";
    return ss.str();

}
