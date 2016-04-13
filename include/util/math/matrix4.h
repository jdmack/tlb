#ifndef TLB_UTIL_MATH_MATRIX4_H_
#define TLB_UTIL_MATH_MATRIX4_H_

#include "vector4.h"
#define M_PI 3.14159265358979323846

struct Vector4;

struct Matrix4
{
    float m_[4][4];   // matrix elements

    // constructors
    Matrix4();
    Matrix4(bool identity);
    Matrix4(const Matrix4 &param);
    // Constructor with 16 parameters to set the values of the matrix
    Matrix4(float, float, float, float,
            float, float, float, float,
            float, float, float, float,
            float, float, float, float);

    // 'get(x,y)' function to read any matrix element
    float get(int x, int y) const;

    void set(int x, int y, float value);
    void set(Matrix4 param);

    // Multiply (matrix-times-matrix)
    Matrix4 multiply(Matrix4 param);

    // Multiply (matrix-times-vector)
    Vector4 multiply(Vector4 param);

    Matrix4 operator*(Matrix4 & param);
    Vector4 operator*(Vector4 & param);

    // Make a rotation matrix about the x axis
    void rotateX(float angle);

    // Make a rotation matrix about the y axis
    void rotateY(float angle);

    // Make a rotation matrix about the z axis
    void rotateZ(float angle);

    // Make a rotation matrix about an arbitrary (unit) axis
    void rotate(float angle, Vector4 axis);

    // Make a non-uniform scaling matrix
    void scale(float x, float y, float z);

    // Make a translation matrix
    void translate(float x, float y, float z);

    // Print the matrix (display all 16 matrix components numerically on the screen in a 4x4 array)
    void print();

    // Transpose the matrix
    void transpose();

    float * pointer();
    void identity();

    void invert();

    void copy_3x3(Matrix4 param);
};

#endif
