#ifndef TLB_UTIL_MATH_VECTOR4_H_
#define TLB_UTIL_MATH_VECTOR4_H_

#include "matrix4.h"

struct Matrix4;

struct Vector4
{
    float x_;
    float y_;
    float z_;
    float w_;

    // constructors
    Vector4();
    // A constructor with three parameters for point coordinates
    Vector4(float x, float y, float z);
    // A constructor with four parameters
    Vector4(float x, float y, float z, float w);

    // accessors
    // Element access 'get': return one of the four coordinates
    float & x() { return x_; }
    float & y() { return y_; }
    float & z() { return z_; }
    float & w() { return w_; }
    float & get(int coordinate);
    float & get(char coordinate);

    // mutators
    // Element access 'set': set each coordinate separately
    void set_x(float x) { x_ = x; }
    void set_y(float y) { y_ = y; }
    void set_z(float z) { z_ = z; }
    void set_w(float w) { w_ = w; }
    void set_coordinates(float x, float y, float z, float w);
    void set(int coordinate, float value);

    // Overload operator '[]' as alternative to 'get' method
    float & operator[](int coordinate);
    float & operator[](char coordinate);

    // Vector addition
    void add(Vector4 param);

    // Overload operator '+' for addition
    Vector4 operator+(Vector4 param);

    // Vector subtraction
    void subtract(Vector4 param);

    // Overload operator '-' for subtraction
    Vector4 operator-(Vector4 param);

    float dot_product(Vector4 param);
    float operator*(Vector4 & param);

    Vector4 multiply(Matrix4 param);
    Vector4 operator*(Matrix4 & param);

    // Dehomogenize (make fourth component equal to 1)
    void dehomogenize();
    
    // Print (display the point's components numerically on the screen)
    void print();
};

#endif