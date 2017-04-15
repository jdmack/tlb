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
    x_ = 0;
    y_ = 0;
    z_ = 0;
}
// A constructor with three parameters for the vector coordinates
Vector3f::Vector3f(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

// accessors
// Element access 'get': return a specific coordinate of the vector
float Vector3f::get(int coordinate) const
{
    switch(coordinate) {
        case 0:
            return x_;
            break;
        case 1:
            return y_;
            break;
        case 2:
            return z_;
            break;
        default:
            return x_;
    }
}

float Vector3f::get(char coordinate) const 
{
    switch(coordinate) {
        case 'x':
            return x_;
            break;
        case 'y':
            return y_;
            break;
        case 'z':
            return z_;
            break;
        default:
            return x_;
    }

}

// mutators
// Element access 'set': set the vector coordinates
void Vector3f::set(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

void Vector3f::set(int i, float val)
{
    switch(i) {
        case 0:
            x_ = val;
            break;
        case 1:
            y_ = val;
            break;
        case 2:
            z_ = val;
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
    x_ = v.x();
    y_ = v.y();
    z_ = v.z();

    return *this;
}

// Vector addition
void Vector3f::add(Vector3f param)
{
    x_ = x_ + param.x();
    y_ = y_ + param.y();
    z_ = z_ + param.z();
}

// Overload operator '+' for addition
Vector3f Vector3f::operator+(Vector3f param)
{
    float newX = x_ + param.x();
    float newY = y_ + param.y();
    float newZ = z_ + param.z();
    
    return Vector3f(newX, newY, newZ);
}

// Vector subtraction
void Vector3f::subtract(Vector3f param)
{
    x_ = x_ - param.x();
    y_ = y_ - param.y();
    z_ = z_ - param.z();
}

// Overload operator '-' for subtraction
Vector3f Vector3f::operator-(Vector3f param)
{
    float newX = x_ - param.x();
    float newY = y_ - param.y();
    float newZ = z_ - param.z();
    
    return Vector3f(newX, newY, newZ);
}

// Negation
void Vector3f::negate()
{
    x_ = -x_;
    y_ = -y_;
    z_ = -z_;
}

// Scale (multiplication with scalar value)
void Vector3f::scale(float param)
{
    x_ *= param;
    y_ *= param;
    z_ *= param;
}
Vector3f Vector3f::operator*(float param)
{
    float newX = x_ * param;
    float newY = y_ * param;
    float newZ = z_ * param;
    return Vector3f(newX, newY, newZ);
}

Vector3f Vector3f::operator/(float param)
{
    float newX = x_ / param;
    float newY = y_ / param;
    float newZ = z_ / param;
    return Vector3f(newX, newY, newZ);
}

// Dot product
float Vector3f::dotProduct(Vector3f param)
{
    float dotProduct = (x_ * param.x())
                       + (y_ * param.y())
                       + (z_ * param.z());

    return dotProduct;
}

// Cross product
Vector3f Vector3f::crossProduct(const Vector3f & param) const
{
    float newX = ((y_ * param.z()) - (z_ * param.y()));
    float newY = ((z_ * param.x()) - (x_ * param.z()));
    float newZ = ((x_ * param.y()) - (y_ * param.x()));
    
    return Vector3f(newX, newY, newZ);
}

Vector3f Vector3f::operator*(Vector3f param)
{
    return crossProduct(param);
}

// Magnitude (length of vector)
float Vector3f::magnitude()
{
    float magnitude = std::sqrt(std::pow(x_, 2) 
                               + std::pow(y_, 2) 
                               + std::pow(z_, 2)
                            );

    return magnitude;
}

// Normalize
void Vector3f::normalize()
{
    float magnitude = this->magnitude();
    x_ /= magnitude;
    y_ /= magnitude;
    z_ /= magnitude;
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

    x_ = w.x();
    y_ = w.y();
    z_ = w.z();
}

void Vector3f::transform(Matrix4f param)
{
    Vector4f v4 = Vector4f(x_, y_, z_);
    v4 = param.multiply(v4);

    x_ = v4.x();
    y_ = v4.y();
    z_ = v4.z();
}
float Vector3f::distanceFrom(Vector3f point)
{
    float x = x_ - point.x();
    float y = y_ - point.y();
    float z = z_ - point.z();

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

    m_[0] = x_;
    m_[1] = y_;
    m_[2] = z_;

    return &m_[0];
}
    */


std::string Vector3f::str()
{
    std::stringstream ss;
    ss << "<" << x_ << ", " << y_ << ", " << z_ << ">";
    return ss.str();
}

std::ostream & operator<<(std::ostream & os, const Vector3f & v)
{
    os << "<" << v.x() << ", " << v.y() << ", " << v.z() << ">";
    return os;
}

