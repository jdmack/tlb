#include <iostream>
#include <sstream>
#include <cmath>
#include "util/math/vector3.h"
#include "util/math/vector4.h"
#include "util/math/matrix4.h"

// constructors
Vector3::Vector3()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
}
// A constructor with three parameters for the vector coordinates
Vector3::Vector3(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

// accessors
// Element access 'get': return a specific coordinate of the vector
float & Vector3::get(int coordinate)
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

float & Vector3::get(char coordinate)
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
void Vector3::set(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

void Vector3::set(int i, float val)
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
float & Vector3::operator[](int coordinate)
{
    return get(coordinate);
}
float & Vector3::operator[](char coordinate)
{
    return get(coordinate);
}

// Vector addition
void Vector3::add(Vector3 param)
{
    x_ = x_ + param.x();
    y_ = y_ + param.y();
    z_ = z_ + param.z();
}

// Overload operator '+' for addition
Vector3 Vector3::operator+(Vector3 param)
{
    float newX = x_ + param.x();
    float newY = y_ + param.y();
    float newZ = z_ + param.z();
    
    return Vector3(newX, newY, newZ);
}

// Vector subtraction
void Vector3::subtract(Vector3 param)
{
    x_ = x_ - param.x();
    y_ = y_ - param.y();
    z_ = z_ - param.z();
}

// Overload operator '-' for subtraction
Vector3 Vector3::operator-(Vector3 param)
{
    float newX = x_ - param.x();
    float newY = y_ - param.y();
    float newZ = z_ - param.z();
    
    return Vector3(newX, newY, newZ);
}

// Negation
void Vector3::negate()
{
    x_ = -x_;
    y_ = -y_;
    z_ = -z_;
}

// Scale (multiplication with scalar value)
void Vector3::scale(float param)
{
    x_ *= param;
    y_ *= param;
    z_ *= param;
}
Vector3 Vector3::operator*(float param)
{
    float newX = x_ * param;
    float newY = y_ * param;
    float newZ = z_ * param;
    return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator/(float param)
{
    float newX = x_ / param;
    float newY = y_ / param;
    float newZ = z_ / param;
    return Vector3(newX, newY, newZ);
}

// Dot product
float Vector3::dotProduct(Vector3 param)
{
    float dotProduct = (x_ * param.x())
                       + (y_ * param.y())
                       + (z_ * param.z());

    return dotProduct;
}

// Cross product
Vector3 Vector3::crossProduct(Vector3 param)
{
    float newX = ((y_ * param.z()) - (z_ * param.y()));
    float newY = ((z_ * param.x()) - (x_ * param.z()));
    float newZ = ((x_ * param.y()) - (y_ * param.x()));
    
    return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator*(Vector3 param)
{
    return crossProduct(param);
}

// Magnitude (length of vector)
float Vector3::magnitude()
{
    float magnitude = std::sqrt(std::pow(x_, 2) 
                               + std::pow(y_, 2) 
                               + std::pow(z_, 2)
                            );

    return magnitude;
}

// Normalize
void Vector3::normalize()
{
    float magnitude = this->magnitude();
    x_ /= magnitude;
    y_ /= magnitude;
    z_ /= magnitude;
}

void Vector3::transform(Matrix4 param)
{
    Vector4 v4 = Vector4(x_, y_, z_);
    v4 = param.multiply(v4);

    x_ = v4.x();
    y_ = v4.y();
    z_ = v4.z();
}
float Vector3::distanceFrom(Vector3 point)
{
    float x = x_ - point.x();
    float y = y_ - point.y();
    float z = z_ - point.z();

    return std::sqrt((x * x) + (y * y) + (z * z));
}



// Print (display the vector's components numerically on the screen)
void Vector3::print()
{
    //std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
}

float Vector3::angle(Vector3 v)
{
    float dotProduct = this->dotProduct(v);
    float thisMag    = this->magnitude();
    float vMag       = v.magnitude();

    return std::acos(dotProduct / (thisMag * vMag));
}

std::string Vector3::str()
{
    std::stringstream ss;
    ss << "<" << x_ << ", " << y_ << ", " << z_ << ">";
    return ss.str();
}

