
#include <sstream>
#include "point.h"
#include "hit_point.h"

HitPoint::HitPoint()
{
	// Default location is center of renderer
    total_= 0;
    current_= 0;
}

HitPoint::HitPoint(int total)
{
    total_= total;
    current_= total;
}

void HitPoint::add_points(int points)
{
    current_ += points;
}

void HitPoint::minus_points(int points)
{
    current_ -= points;
}


std::string HitPoint::to_string()
{
    std::stringstream ss;
    ss << "(" << current_ << "," << total_ << ")";
    return ss.str();
}
