#include <cmath>
#include <sstream>
#include <string>
#include "movement.h"
#include "point.h"
#include "gameObject.h"
#include "util/logger.h"

Movement::Movement(Vector vector, Point start, Point destination)
{
    vector_ = vector;
    start_ = start;
    destination_ = destination;
    clockwise_ = false;
    degrees_ = 0;
}

std::string Movement::toString()
{
    std::stringstream ss;
    ss << "Movement(Start:" << start_.toString() << ", Destination:" << destination_.toString() << ")";
    return ss.str();

}
