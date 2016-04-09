#ifndef TLB_UTIL_MATH_VECTOR3_H_
#define TLB_UTIL_MATH_VECTOR3_H_

#include <string>
#include "matrix4.h"
#define kPi 3.14159265359

struct Vector3
{
    float x_;
    float y_;
    float z_;

    // constructors
    Vector3();
    // A constructor with three parameters for the vector coordinates
    Vector3(float x, float y, float z);

    // accessors
    // Element access 'get': return a specific coordinate of the vector
    float & x() { return x_; }
    float & y() { return y_; }
    float & z() { return z_; }
    float & get(int coordinate);
    float & get(char coordinate);

    // mutators
    // Element access 'set': set the vector coordinates
    void set_x(float x) { x_ = x; }
    void set_y(float y) { y_ = y; }
    void set_z(float z) { z_ = z; }
    void set(float x, float y, float z);
    void set(int i, float val);

    // Overload operator '[]' as alternative to 'get' method
    float & operator[](int coordinate);
    float & operator[](char coordinate);

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
    float dot_product(Vector3 param);

    // Cross product
    Vector3 cross_product(Vector3 param);
    Vector3 operator*(Vector3 param);

    // Magnitude (length of vector)
    float magnitude();

    // Normalize
    void normalize();

    void transform(Matrix4 param);
    
    float distance_from(Vector3 point);

    // Print (display the vector's components numerically on the screen)
    void print();
    std::string str();

    float angle(Vector3 v);

};

#endif
