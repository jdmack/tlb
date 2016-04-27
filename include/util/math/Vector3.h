#ifndef TLB_UTIL_MATH_VECTOR3_H_
#define TLB_UTIL_MATH_VECTOR3_H_

#include <string>
#include "util/math/Vector4.h"
#include "util/math/Matrix4.h"
#define kPi 3.14159265359

class Vector4;
class Matrix4;

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
        const float & x() { return x_; }
        const float & y() { return y_; }
        const float & z() { return z_; }
        //const float & get(int coordinate);
        //const float & get(char coordinate);

        // mutators
        // Element access 'set': set the vector coordinates
        void setX(float x) { x_ = x; }
        void setY(float y) { y_ = y; }
        void setZ(float z) { z_ = z; }
        void set(float x, float y, float z);
        void set(int i, float val);

        // Overload operator '[]' as alternative to 'get' method
        //const float & operator[](int coordinate);
        //const float & operator[](char coordinate);

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
        Vector3 crossProduct(Vector3 param);
        Vector3 operator*(Vector3 param);

        // Magnitude (length of vector)
        float magnitude();

        // Normalize
        void normalize();

        void transform(Matrix4 param);
        
        float distanceFrom(Vector3 point);

        // Print (display the vector's components numerically on the screen)
        void print();
        std::string str();

        float angle(Vector3 v);

};

#endif
