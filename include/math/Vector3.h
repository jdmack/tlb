#ifndef TLB_UTIL_MATH_VECTOR3_H_
#define TLB_UTIL_MATH_VECTOR3_H_

#include <string>
#include "math/Vector4.h"
#include "math/Matrix4.h"


class Vector3
{
    private:
        float x_;
        float y_;
        float z_;

    public:
        // constructors
        Vector3();
        // A constructor with three parameters for the vector coordinates
        Vector3(float x, float y, float z);

        // accessors
        // Element access 'get': return a specific coordinate of the vector
        float x() const { return x_; }
        float y() const { return y_; }
        float z() const { return z_; }
        float get(int coordinate) const;
        float get(char coordinate) const;

        // mutators
        // Element access 'set': set the vector coordinates
        void setX(float x) { x_ = x; }
        void setY(float y) { y_ = y; }
        void setZ(float z) { z_ = z; }
        void set(float x, float y, float z);
        void set(int i, float val);

        // Overload operator '[]' as alternative to 'get' method
        float operator[](int coordinate) const;
        float operator[](char coordinate) const;

        // Copy assignment operator
        Vector3 & operator=(Vector3 v);

        // Vector addition
        void add(Vector3 param);

        // Overload operator '+' for addition
        Vector3 operator+(Vector3 param);

        // Vector subtraction
        void subtract(Vector3 param);

        // Overload operator '-' for subtraction
        Vector3 operator-(Vector3 param);

        // Negation
        void negate();

        // Scale (multiplication with scalar value)
        void scale(float param);
        Vector3 operator*(float param);
        Vector3 operator/(float param);

        // Dot product
        float dotProduct(Vector3 param);

        // Cross product
        Vector3 crossProduct(const Vector3 & param) const;
        Vector3 operator*(Vector3 param);

        // Magnitude (length of vector)
        float magnitude();

        // Normalize
        void normalize();

        void transform(Matrix4 param);

        void rotate(float angle, const Vector3 axis);
        
        float distanceFrom(Vector3 point);

        // Print (display the vector's components numerically on the screen)
        void print();
        std::string str();

        float angle(Vector3 v);

};

#endif
