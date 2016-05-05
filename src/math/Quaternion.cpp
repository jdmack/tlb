#include <cmath>

#include "math/Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}

// accessors
// Element access 'get': return one of the four coordinates
float Quaternion::get(int coordinate) const
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

float Quaternion::get(char coordinate) const
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
void Quaternion::setCoordinates(float x, float y, float z, float w)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}

void Quaternion::set(int coordinate, float value)
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
float Quaternion::operator[](int coordinate) const
{
    return get(coordinate);
}

float Quaternion::operator[](char coordinate) const
{
    return get(coordinate);
}

void Quaternion::normalize()
{
    float length = sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);

    x_ /= length;
    y_ /= length;
    z_ /= length;
    w_ /= length;
}

Quaternion Quaternion::conjugate()
{
    Quaternion ret(-x_, -y_, -z_, w_);
    return ret;
}

Quaternion Quaternion::operator*(const Quaternion & q)
{
    const float w = (w_ * w_) - (x_ * x_) - (y_ * y_) - (z_ * z_);
    const float x = (x_ * x_) + (w_ * x_) + (y_ * z_) - (z_ * y_);
    const float y = (y_ * w_) + (w_ * y_) + (z_ * x_) - (x_ * z_);
    const float z = (z_ * w_) + (w_ * z_) + (x_ * y_) - (y_ * x_);

    Quaternion ret(x, y, z, w);

    return ret;
}

Quaternion Quaternion::operator*(const Vector3 & v)
{
    const float w = - (x_ * v.x()) - (y_ * v.y()) - (z_ * v.z());
    const float x =   (w_ * v.x()) + (y_ * v.z()) - (z_ * v.y());
    const float y =   (w_ * v.y()) + (z_ * v.x()) - (x_ * v.z());
    const float z =   (w_ * v.z()) + (x_ * v.y()) - (y_ * v.x());

    Quaternion ret(x, y, z, w);

    return ret;
}
















