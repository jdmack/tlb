#include <iostream>
#include "math/Vector4f.h"
#include "math/Matrix4f.h"


// constructors
Vector4f::Vector4f()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
    w_ = 1;
}

// A constructor with three parameters for point coordinates
Vector4f::Vector4f(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = 1;
}

// A constructor with four parameters
Vector4f::Vector4f(float x, float y, float z, float w)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}

// accessors
// Element access 'get': return one of the four coordinates
float Vector4f::get(int coordinate) const
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
        case 3:
            return w_;
            break;
        default:
            return x_;
    }
}

float Vector4f::get(char coordinate) const
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
        case 'w':
            return w_;
            break;
        default:
            return x_;
    }

}

// mutators
// Element access 'set': set the vector coordinates
void Vector4f::setCoordinates(float x, float y, float z, float w)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}
void Vector4f::set(int coordinate, float value)
{
    switch(coordinate) {
        case 0:
            x_ = value;
            break;
        case 1:
            y_ = value;
            break;
        case 2:
            z_ = value;
            break;
        case 3:
            w_ = value;
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
    x_ = x_ + param.x();
    y_ = y_ + param.y();
    z_ = z_ + param.z();
    w_ = w_ + param.w();
}

// Overload operator '+' for addition
Vector4f Vector4f::operator+(Vector4f param)
{
    float newX = x_ + param.x();
    float newY = y_ + param.y();
    float newZ = z_ + param.z();
    float newW = w_ + param.w();

    return Vector4f(newX, newY, newZ, newW);
}

// Vector subtraction
void Vector4f::subtract(Vector4f param)
{
    x_ = x_ - param.x();
    y_ = y_ - param.y();
    z_ = z_ - param.z();
    w_ = w_ - param.w();
}

// Overload operator '-' for subtraction
Vector4f Vector4f::operator-(Vector4f param)
{
    float newX = x_ - param.x();
    float newY = y_ - param.y();
    float newZ = z_ - param.z();
    float newW = w_ - param.w();

    return Vector4f(newX, newY, newZ, newW);
}

// Dot product
float Vector4f::dotProduct(Vector4f param)
{
    float dotProduct = (x_ * param.x())
                       + (y_ * param.y())
                       + (z_ * param.z())
                       + (w_ * param.w());

    return dotProduct;
}

// Multiply (vector-times-matrix)
Vector4f Vector4f::multiply(Matrix4f param)
{
    Vector4f thisV = Vector4f(x_, y_, z_, w_);
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
    x_ /= w_;
    y_ /= w_;
    z_ /= w_;
    w_ /= w_;
}

const float * Vector4f::pointer()
{
    m_[0] = x_;
    m_[1] = y_;
    m_[2] = z_;
    m_[3] = w_;
    return &m_[0];
}

// Print (display the point's components numerically on the screen)
void Vector4f::print()
{
    std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ", " << w_ << ")" << std::endl;
}
