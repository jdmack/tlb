#include <iostream>
#include "math/Vector4f.h"
#include "math/Matrix4f.h"


// constructors
Vector4f::Vector4f()
{
    m_[0] = 0;
    m_[1] = 0;
    m_[2] = 0;
    m_[3] = 1;
}

// A constructor with three parameters for point coordinates
Vector4f::Vector4f(float x, float y, float z)
{
    m_[0] = x;
    m_[1] = y;
    m_[2] = z;
    m_[3] = 1;
}

// A constructor with four parameters
Vector4f::Vector4f(float x, float y, float z, float w)
{
    m_[0] = x;
    m_[1] = y;
    m_[2] = z;
    m_[3] = w;
}

// accessors
// Element access 'get': return one of the four coordinates
float Vector4f::get(int coordinate) const
{
    switch(coordinate) {
        case 0:
            return m_[0];
            break;
        case 1:
            return m_[1];
            break;
        case 2:
            return m_[2];
            break;
        case 3:
            return m_[3];
            break;
        default:
            return m_[0];
    }
}

float Vector4f::get(char coordinate) const
{
    switch(coordinate) {
        case 'x':
            return m_[0];
            break;
        case 'y':
            return m_[1];
            break;
        case 'z':
            return m_[2];
            break;
        case 'w':
            return m_[3];
            break;
        default:
            return m_[0];
    }

}

// mutators
// Element access 'set': set the vector coordinates
void Vector4f::setCoordinates(float x, float y, float z, float w)
{
    m_[0] = x;
    m_[1] = y;
    m_[2] = z;
    m_[3] = w;
}
void Vector4f::set(int coordinate, float value)
{
    switch(coordinate) {
        case 0:
            m_[0] = value;
            break;
        case 1:
            m_[1] = value;
            break;
        case 2:
            m_[2] = value;
            break;
        case 3:
            m_[3] = value;
            break;
    }
}

// Overload operator '[]' as alternative to 'get' method
float Vector4f::operator[](int coordinate) const
{
    return get(coordinate);
}
float Vector4f::operator[](char coordinate) const
{
    return get(coordinate);
}

// Vector addition
void Vector4f::add(Vector4f param)
{
    m_[0] = m_[0] + param.x();
    m_[1] = m_[1] + param.y();
    m_[2] = m_[2] + param.z();
    m_[3] = m_[3] + param.w();
}

// Overload operator '+' for addition
Vector4f Vector4f::operator+(Vector4f param)
{
    float newX = m_[0] + param.x();
    float newY = m_[1] + param.y();
    float newZ = m_[2] + param.z();
    float newW = m_[3] + param.w();

    return Vector4f(newX, newY, newZ, newW);
}

// Vector subtraction
void Vector4f::subtract(Vector4f param)
{
    m_[0] = m_[0] - param.x();
    m_[1] = m_[1] - param.y();
    m_[2] = m_[2] - param.z();
    m_[3] = m_[3] - param.w();
}

// Overload operator '-' for subtraction
Vector4f Vector4f::operator-(Vector4f param)
{
    float newX = m_[0] - param.x();
    float newY = m_[1] - param.y();
    float newZ = m_[2] - param.z();
    float newW = m_[3] - param.w();

    return Vector4f(newX, newY, newZ, newW);
}

// Dot product
float Vector4f::dotProduct(Vector4f param)
{
    float dotProduct = (m_[0] * param.x())
                       + (m_[1] * param.y())
                       + (m_[2] * param.z())
                       + (m_[3] * param.w());

    return dotProduct;
}

// Multiply (vector-times-matrix)
Vector4f Vector4f::multiply(Matrix4f param)
{
    Vector4f thisV = Vector4f(m_[0], m_[1], m_[2], m_[3]);
    Vector4f result = param.multiply(thisV);

    return result;
}

float Vector4f::operator*(Vector4f & param)
{
    return dotProduct(param);
}

Vector4f Vector4f::operator*(Matrix4f & param)
{
    return multiply(param);
}

// Dehomogenize (make fourth component equal to 1)
void Vector4f::dehomogenize()
{
    // TODO: account for W = 0;
    m_[0] /= m_[3];
    m_[1] /= m_[3];
    m_[2] /= m_[3];
    m_[3] /= m_[3];
}

const float * Vector4f::pointer()
{
    m_[0] = m_[0];
    m_[1] = m_[1];
    m_[2] = m_[2];
    m_[3] = m_[3];
    return &m_[0];
}

std::ostream & operator<<(std::ostream & os, const Vector4f & v)
{
        os << "<" << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w() << ">";
            return os;
}

