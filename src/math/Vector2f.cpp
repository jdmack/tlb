
#include <sstream>
#include <cmath>
#include "math/Vector2f.h"

Vector2f::Vector2f()
{
	// Default location is center of renderer
    m_[0]= 0;
    m_[1]= 0;
}

Vector2f::Vector2f(float x, float y)
{
    m_[0]= x;
    m_[1]= y;
}

std::string Vector2f::toString()
{
    std::stringstream ss;
    ss << "(" << m_[0] << "," << m_[1] << ")";
    return ss.str();
}

Vector2f & Vector2f::operator=(Vector2f v)
{
    m_[0] = v.x();
    m_[1] = v.y();
    return *this;
}

bool Vector2f::operator==(const Vector2f &other) const
{
    if((m_[0] == other.x()) && (m_[1] == other.y())) {
        return true;
    }
    else {
        return false;
    }
}

bool Vector2f::operator!=(const Vector2f &other) const
{
    return !(*this == other);
}

float Vector2f::distanceFrom(Vector2f point)
{
    float xDistance = point.x() - m_[0];
    float yDistance = point.y() - m_[1];
    return sqrt((xDistance * xDistance) + (yDistance * yDistance));
}

const float * Vector2f::pointer()
{
        return &m_[0];
}


std::ostream & operator<<(std::ostream & os, const Vector2f & v)
{
        os << "(" << v.x() << ", " << v.y() << ">";
        return os;
}
