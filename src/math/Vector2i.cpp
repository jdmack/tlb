
#include <sstream>
#include <cmath>
#include "math/Vector2i.h"

Vector2i::Vector2i()
{
	// Default location is center of renderer
    m_[0]= 0;
    m_[1]= 0;
}

Vector2i::Vector2i(int x, int y)
{
    m_[0]= x;
    m_[1]= y;
}

std::string Vector2i::toString()
{
    std::stringstream ss;
    ss << "(" << m_[0] << "," << m_[1] << ")";
    return ss.str();
}

bool Vector2i::operator==(const Vector2i &other) const
{
    if((m_[0] == other.x()) && (m_[1] == other.y())) {
        return true;
    }
    else {
        return false;
    }
}

bool Vector2i::operator!=(const Vector2i &other) const
{
    return !(*this == other);
}

int Vector2i::distanceFrom(Vector2i point)
{
    int xDistance = point.x() - m_[0];
    int yDistance = point.y() - m_[1];
    return sqrt((xDistance * xDistance) + (yDistance * yDistance));
}

std::ostream & operator<<(std::ostream & os, const Vector2i & v)
{
        os << "(" << v.x() << ", " << v.y() << ">";
        return os;
}
