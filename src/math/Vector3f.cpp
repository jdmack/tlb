#include <iostream>
#include <sstream>
#include <cmath>
#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "math/Matrix4f.h"
#include "math/Math.h"
#include "math/Quaternion.h"

// constructors
Vector3f::Vector3f()
{
    m_[0] = 0;
    m_[1] = 0;
    m_[2] = 0;
}
// A constructor with three parameters for the vector coordinates
Vector3f::Vector3f(float x, float y, float z)
{
    m_[0] = x;
    m_[1] = y;
    m_[2] = z;
}

// accessors
// Element access 'get': return a specific coordinate of the vector
float Vector3f::get(int coordinate) const
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
        default:
            return m_[0];
    }
}

float Vector3f::get(char coordinate) const 
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
        default:
            return m_[0];
    }

}

// mutators
// Element access 'set': set the vector coordinates
void Vector3f::set(float x, float y, float z)
{
    m_[0] = x;
    m_[1] = y;
    m_[2] = z;
}

void Vector3f::set(int i, float val)
{
    switch(i) {
        case 0:
            m_[0] = val;
            break;
        case 1:
            m_[1] = val;
            break;
        case 2:
            m_[2] = val;
            break;
        default:
            break;
    }
}

// Overload operator '[]' as alternative to 'get' method

float Vector3f::operator[](int coordinate) const
{
    return get(coordinate);
}
float Vector3f::operator[](char coordinate) const
{
    return get(coordinate);
}

// Copy assignment operator
Vector3f & Vector3f::operator=(Vector3f v)
{
    m_[0] = v.x();
    m_[1] = v.y();
    m_[2] = v.z();

    return *this;
}

// Vector addition
void Vector3f::add(Vector3f param)
{
    m_[0] = m_[0] + param.x();
    m_[1] = m_[1] + param.y();
    m_[2] = m_[2] + param.z();
}

// Overload operator '+' for addition
Vector3f Vector3f::operator+(Vector3f param)
{
    float newX = m_[0] + param.x();
    float newY = m_[1] + param.y();
    float newZ = m_[2] + param.z();
    
    return Vector3f(newX, newY, newZ);
}

// Vector subtraction
void Vector3f::subtract(Vector3f param)
{
    m_[0] = m_[0] - param.x();
    m_[1] = m_[1] - param.y();
    m_[2] = m_[2] - param.z();
}

// Overload operator '-' for subtraction
Vector3f Vector3f::operator-(Vector3f param)
{
    float newX = m_[0] - param.x();
    float newY = m_[1] - param.y();
    float newZ = m_[2] - param.z();
    
    return Vector3f(newX, newY, newZ);
}

// Negation
void Vector3f::negate()
{
    m_[0] = -m_[0];
    m_[1] = -m_[1];
    m_[2] = -m_[2];
}

// Scale (multiplication with scalar value)
void Vector3f::scale(float param)
{
    m_[0] *= param;
    m_[1] *= param;
    m_[2] *= param;
}
Vector3f Vector3f::operator*(float param)
{
    float newX = m_[0] * param;
    float newY = m_[1] * param;
    float newZ = m_[2] * param;
    return Vector3f(newX, newY, newZ);
}

Vector3f Vector3f::operator/(float param)
{
    float newX = m_[0] / param;
    float newY = m_[1] / param;
    float newZ = m_[2] / param;
    return Vector3f(newX, newY, newZ);
}

// Dot product
float Vector3f::dotProduct(Vector3f param)
{
    float dotProduct = (m_[0] * param.x())
                       + (m_[1] * param.y())
                       + (m_[2] * param.z());

    return dotProduct;
}

// Cross product
Vector3f Vector3f::crossProduct(const Vector3f & param) const
{
    float newX = ((m_[1] * param.z()) - (m_[2] * param.y()));
    float newY = ((m_[2] * param.x()) - (m_[0] * param.z()));
    float newZ = ((m_[0] * param.y()) - (m_[1] * param.x()));
    
    return Vector3f(newX, newY, newZ);
}

Vector3f Vector3f::operator*(Vector3f param)
{
    return crossProduct(param);
}

// Magnitude (length of vector)
float Vector3f::magnitude()
{
    float magnitude = std::sqrt(std::pow(m_[0], 2) 
                               + std::pow(m_[1], 2) 
                               + std::pow(m_[2], 2)
                            );

    return magnitude;
}

// Normalize
void Vector3f::normalize()
{
    float magnitude = this->magnitude();
    m_[0] /= magnitude;
    m_[1] /= magnitude;
    m_[2] /= magnitude;
}

void Vector3f::rotate(float angle, const Vector3f axis)
{
    const float sinHalfAngle = sinf(toRadian(angle / 2));
    const float cosHalfAngle = cosf(toRadian(angle / 2));

    const float rx = axis.x() * sinHalfAngle;
    const float ry = axis.y() * sinHalfAngle;
    const float rz = axis.z() * sinHalfAngle;
    const float rw = cosHalfAngle;

    Quaternion rotationQ(rx, ry, rz, rw);

    Quaternion conjugateQ = rotationQ.conjugate();

    Quaternion w = rotationQ * (*this) * conjugateQ;

    m_[0] = w.x();
    m_[1] = w.y();
    m_[2] = w.z();
}

void Vector3f::transform(Matrix4f param)
{
    Vector4f v4 = Vector4f(m_[0], m_[1], m_[2]);
    v4 = param.multiply(v4);

    m_[0] = v4.x();
    m_[1] = v4.y();
    m_[2] = v4.z();
}
float Vector3f::distanceFrom(Vector3f point)
{
    float x = m_[0] - point.x();
    float y = m_[1] - point.y();
    float z = m_[2] - point.z();

    return std::sqrt((x * x) + (y * y) + (z * z));
}

float Vector3f::angle(Vector3f v)
{
    float dotProduct = this->dotProduct(v);
    float thisMag    = this->magnitude();
    float vMag       = v.magnitude();

    return std::acos(dotProduct / (thisMag * vMag));
}

/*
const float * Vector3f::pointer()
{

    m_[0] = m_[0];
    m_[1] = m_[1];
    m_[2] = m_[2];

    return &m_[0];
}
    */


std::string Vector3f::str()
{
    std::stringstream ss;
    ss << "<" << m_[0] << ", " << m_[1] << ", " << m_[2] << ">";
    return ss.str();
}

std::ostream & operator<<(std::ostream & os, const Vector3f & v)
{
    os << "<" << v.x() << ", " << v.y() << ", " << v.z() << ">";
    return os;
}

