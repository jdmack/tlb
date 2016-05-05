#ifndef TLB_UTIL_MATH_QUATERNION_H_
#define TLB_UTIL_MATH_QUATERNION_H_

#include "math/Vector3.h"


class Quaternion
{
    private:
        float x_;
        float y_;
        float z_;
        float w_;

    public:
        Quaternion(float x, float y, float z, float w);

        // accessors
        // Element access 'get': return one of the four coordinates
        float x() const { return x_; }
        float y() const { return y_; }
        float z() const { return z_; }
        float w() const { return w_; }
        float get(int coordinate) const;
        float get(char coordinate) const;

        // mutators
        // Element access 'set': set each coordinate separately
        void setX(float x) { x_ = x; }
        void setY(float y) { y_ = y; }
        void setZ(float z) { z_ = z; }
        void setW(float w) { w_ = w; }
        void setCoordinates(float x, float y, float z, float w);
        void set(int coordinate, float value);

        // Overload operator '[]' as alternative to 'get' method
        float operator[](int coordinate) const;
        float operator[](char coordinate) const;



        Quaternion operator*(const Quaternion & q);
        Quaternion operator*(const Vector3 & v);

        void normalize();
        Quaternion conjugate();
};

#endif
