
#include <sstream>
#include "Point.h"
#include "HitPoint.h"

HitPoint::HitPoint()
{
    total_= 0;
    current_= 0;
}

HitPoint::HitPoint(int total)
{
    total_= total;
    current_= total;
}

void HitPoint::addPoints(int points)
{
    current_ += points;
}

void HitPoint::minusPoints(int points)
{
    current_ -= points;
}

bool HitPoint::empty()
{
    if(current_ <= 0) {
        return true;
    }
    return false;
}

std::string HitPoint::toString()
{
    std::stringstream ss;
    ss << "(" << current_ << "," << total_ << ")";
    return ss.str();
}
