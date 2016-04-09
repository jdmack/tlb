#include <iostream>
#include "util/math/vector4.h"

// constructors
Vector4::Vector4()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
    w_ = 1;
}

// A constructor with three parameters for point coordinates
Vector4::Vector4(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = 1;
}

// A constructor with four parameters
Vector4::Vector4(float x, float y, float z, float w)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}

// accessors
// Element access 'get': return one of the four coordinates
float & Vector4::get(int coordinate)
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

float & Vector4::get(char coordinate)
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
void Vector4::set_coordinates(float x, float y, float z, float w)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}
void Vector4::set(int coordinate, float value)
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
float & Vector4::operator[](int coordinate)
{
    return get(coordinate);
}
float & Vector4::operator[](char coordinate)
{
    return get(coordinate);
}

// Vector addition
void Vector4::add(Vector4 param)
{
    x_ = x_ + param.x();
    y_ = y_ + param.y();
    z_ = z_ + param.z();
    w_ = w_ + param.w();
}

// Overload operator '+' for addition
Vector4 Vector4::operator+(Vector4 param)
{
    float new_x = x_ + param.x();
    float new_y = y_ + param.y();
    float new_z = z_ + param.z();
    float new_w = w_ + param.w();

    return Vector4(new_x, new_y, new_z, new_w);
}

// Vector subtraction
void Vector4::subtract(Vector4 param)
{
    x_ = x_ - param.x();
    y_ = y_ - param.y();
    z_ = z_ - param.z();
    w_ = w_ - param.w();
}

// Overload operator '-' for subtraction
Vector4 Vector4::operator-(Vector4 param)
{
    float new_x = x_ - param.x();
    float new_y = y_ - param.y();
    float new_z = z_ - param.z();
    float new_w = w_ - param.w();

    return Vector4(new_x, new_y, new_z, new_w);
}

// Dot product
float Vector4::dot_product(Vector4 param)
{
    float dot_product = (x_ * param.x())
                       + (y_ * param.y())
                       + (z_ * param.z())
                       + (w_ * param.w());

    return dot_product;
}

// Multiply (vector-times-matrix)
Vector4 Vector4::multiply(Matrix4 param)
{
    Vector4 this_v = Vector4(x_, y_, z_, w_);
    Vector4 result = param.multiply(this_v);

    return result;
}

float Vector4::operator*(Vector4 & param)
{
    return dot_product(param);
}

Vector4 Vector4::operator*(Matrix4 & param)
{
    return multiply(param);
}

// Dehomogenize (make fourth component equal to 1)
void Vector4::dehomogenize()
{
    // TODO: account for W = 0;
    x_ /= w_;
    y_ /= w_;
    z_ /= w_;
    w_ /= w_;
}

// Print (display the point's components numerically on the screen)
void Vector4::print()
{
    std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ", " << w_ << ")" << std::endl;
}
