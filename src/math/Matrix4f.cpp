#include <iostream> 
#include <iomanip>
#include <math.h>

#include "math/Math.h"
#include "math/Matrix4f.h"
#include "math/Vector4f.h"
#include "Transform.h"

// Note: Matrix is stored row-major.

Matrix4f::Matrix4f()
{
    for(int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m_[row][col] = 0;
        }
    }
}

Matrix4f::Matrix4f(bool identity)
{
    if(identity) this->identity();
}

Matrix4f::Matrix4f(const Matrix4f &param)
{
    for(int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m_[row][col] = param.get(row, col);
        }
    }
} 

// Constructor with 16 parameters to set the values of the matrix
Matrix4f::Matrix4f(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33)
{
    m_[0][0] = m00;
    m_[0][1] = m01;
    m_[0][2] = m02;
    m_[0][3] = m03;
    m_[1][0] = m10;
    m_[1][1] = m11;
    m_[1][2] = m12;
    m_[1][3] = m13;
    m_[2][0] = m20;
    m_[2][1] = m21;
    m_[2][2] = m22;
    m_[2][3] = m23;
    m_[3][0] = m30;
    m_[3][1] = m31;
    m_[3][2] = m32;
    m_[3][3] = m33;
}


// 'get(x,y)' function to read any matrix element
float Matrix4f::get(int x, int y) const
{
    return m_[x][y];
}

void Matrix4f::set(int x, int y, float value)
{
    m_[x][y] = value;
}

void Matrix4f::set(Matrix4f param)
{
    for(int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m_[row][col] = param.get(row,col);
        }
    }
}

// Copy assignment operator
Matrix4f & Matrix4f::operator=(Matrix4f m)
{
    m_[0][0] = m.get(0,0);
    m_[0][1] = m.get(0,1);
    m_[0][2] = m.get(0,2);
    m_[0][3] = m.get(0,3);
    m_[1][0] = m.get(1,0);
    m_[1][1] = m.get(1,1);
    m_[1][2] = m.get(1,2);
    m_[1][3] = m.get(1,3);
    m_[2][0] = m.get(2,0);
    m_[2][1] = m.get(2,1);
    m_[2][2] = m.get(2,2);
    m_[2][3] = m.get(2,3);
    m_[3][0] = m.get(3,0);
    m_[3][1] = m.get(3,1);
    m_[3][2] = m.get(3,2);
    m_[3][3] = m.get(3,3);
    return *this;
}
// Multiply (matrix-times-matrix)
Matrix4f Matrix4f::multiply(Matrix4f param)
{
    Matrix4f result;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            for (int i = 0; i < 4; i++) {
                result.set(row, col, result.get(row, col) + m_[row][i] * param.get(i, col));
            }
        }
    }

    return result;
}

// Multiply (matrix-times-vector)
Vector4f Matrix4f::multiply(Vector4f param)
{
    Vector4f result;
    transpose();
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.set(row, result.get(row) + m_[row][col] * param.get(col));
        }
    }
    transpose();
    return result;
}

Matrix4f Matrix4f::operator*(Matrix4f & param)
{
    return multiply(param);
}

Vector4f Matrix4f::operator*(Vector4f & param)
{
    return multiply(param);
}

// Make a rotation matrix about the x axis
void Matrix4f::rotateX(float angle)
{
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians
     Matrix4f param(1,          0,           0, 0,
                   0, cos(angle), -sin(angle), 0,
                   0, sin(angle),  cos(angle), 0,
                   0,          0,           0, 1);
    set(multiply(param));
}

// Make a rotation matrix about the y axis
// angle in degrees
void Matrix4f::rotateY(float angle)
{
    angle = (angle / 180.0) * M_PI;  // convert from degrees to radians
    Matrix4f param( cos(angle), 0, sin(angle), 0, 
                             0, 1,          0, 0, 
                   -sin(angle), 0, cos(angle), 0, 
                             0, 0,          0, 1);
    set(multiply(param));
}

// Make a rotation matrix about the z axis
void Matrix4f::rotateZ(float angle)
{
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians  
    Matrix4f param(cos(angle), -sin(angle), 0, 0,
                  sin(angle),  cos(angle), 0, 0,
                           0,           0, 1, 0,
                           0,           0, 0, 1);
    set(multiply(param));
}

// Make a rotation matrix about an arbitrary (unit) axis
void Matrix4f::rotate(float angle, Vector4f axis)
{
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians
    float x = axis.get('x');
    float y = axis.get('y'); 
    float z = axis.get('z');

    float m00 = 1 + (1 - cos(angle)) * (x * x - 1);
    float m01 = -z * sin(angle) + (1 - cos(angle)) * x * y;
    float m02 = y * sin(angle) + (1 - cos(angle)) * x * z;
    float m03 = 0;

    float m10 = z * sin(angle) + (1 - cos(angle)) * y * x;
    float m11 = 1 + (1 - cos(angle)) * (y * y - 1);
    float m12 = -x * sin(angle) + (1 - cos(angle)) * y * z;
    float m13 = 0;

    float m20 = -y * sin(angle) + (1 - cos(angle)) * z * x;
    float m21 = x * sin(angle) + (1 - cos(angle)) * z * y;
    float m22 = 1 + (1 - cos(angle)) * (z * z - 1);
    float m23 = 0;

    float m30 = 0;
    float m31 = 0;
    float m32 = 0;
    float m33 = 1;

    Matrix4f param(m00, m01, m02, m03,
                  m10, m11, m12, m13,
                  m20, m21, m22, m23,
                  m30, m31, m32, m33);

    set(multiply(param));
}

// Make a non-uniform scaling matrix
void Matrix4f::scale(float x, float y, float z)
{
    Matrix4f param(x,0,0,0,
                  0,y,0,0,
                  0,0,z,0,
                  0,0,0,1);

    set(multiply(param));
}

// Make a translation matrix
void Matrix4f::translate(float x, float y, float z)
{
    Matrix4f param(1,0,0,x,
                  0,1,0,y,
                  0,0,1,z,
                  0,0,0,1);
    param.transpose();
    set(multiply(param));
}

// Print the matrix (display all 16 matrix components numerically on the screen in a 4x4 array)
void Matrix4f::print()
{
    transpose();
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            std::cout << std::setw(6) << m_[row][col] << " ";
        }
        std::cout << std::endl;
    }
    transpose();
    std::cout << std::endl;
}

// Transpose the matrix
void Matrix4f::transpose()
{
    Matrix4f temp;
    temp.set(*this);

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m_[row][col] = temp.get(col, row);
        }
    }
}

float * Matrix4f::pointer()
{
    return &m_[0][0];
}

void Matrix4f::identity()
{
    float ident[4][4] = {{1, 0, 0, 0},
                          {0, 1, 0, 0},
                          {0, 0, 1, 0},
                          {0, 0, 0, 1}};

    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            m_[row][col] = ident[row][col];
        }
    }
}

void Matrix4f::invert()
{
    /*
    Matrix4f rotation(m_[0][0], m_[0][1], m_[0][2], 0,
                     m_[1][0], m_[1][1], m_[1][2], 0,
                     m_[2][0], m_[2][1], m_[2][2], 0,
                           0,       0,       0, 1);

    Matrix4f translation(1, 0, 0, -m_[0][3],
                        0, 1, 0, -m_[1][3],
                        0, 0, 1, -m_[2][3],
                        0, 0, 0,        1);

    rotation.transpose();
    set(translation.multiply(rotation));
    */
    float det = m_[0][0] * m_[1][1] * m_[2][2] * m_[3][3] + m_[0][0] * m_[1][2] * m_[2][3] * m_[3][1] + m_[0][0] * m_[1][3] * m_[2][1] * m_[3][2]
               + m_[0][1] * m_[1][0] * m_[2][3] * m_[3][2] + m_[0][1] * m_[1][2] * m_[2][0] * m_[3][3] + m_[0][1] * m_[1][3] * m_[2][2] * m_[3][0]
               + m_[0][2] * m_[1][0] * m_[2][1] * m_[3][3] + m_[0][2] * m_[1][1] * m_[2][3] * m_[3][0] + m_[0][2] * m_[1][3] * m_[2][0] * m_[3][1]
               + m_[0][3] * m_[1][0] * m_[2][2] * m_[3][1] + m_[0][3] * m_[1][1] * m_[2][0] * m_[3][2] + m_[0][3] * m_[1][2] * m_[2][1] * m_[3][0]
               - m_[0][0] * m_[1][1] * m_[2][3] * m_[3][2] - m_[0][0] * m_[1][2] * m_[2][1] * m_[3][3] - m_[0][0] * m_[1][3] * m_[2][2] * m_[3][1]
               - m_[0][1] * m_[1][0] * m_[2][2] * m_[3][3] - m_[0][1] * m_[1][2] * m_[2][3] * m_[3][0] - m_[0][1] * m_[1][3] * m_[2][0] * m_[3][2]
               - m_[0][2] * m_[1][0] * m_[2][3] * m_[3][1] - m_[0][2] * m_[1][1] * m_[2][0] * m_[3][3] - m_[0][2] * m_[1][3] * m_[2][1] * m_[3][0]
               - m_[0][3] * m_[1][0] * m_[2][1] * m_[3][2] - m_[0][3] * m_[1][1] * m_[2][2] * m_[3][0] - m_[0][3] * m_[1][2] * m_[2][0] * m_[3][1];

    float b[4][4];

    b[0][0] = m_[1][1] * m_[2][2] * m_[3][3] + m_[1][2] * m_[2][3] * m_[3][1] + m_[1][3] * m_[2][1] * m_[3][2] - m_[1][1] * m_[2][3] * m_[3][2] - m_[1][2] * m_[2][1] * m_[3][3] - m_[1][3] * m_[2][2] * m_[3][1];
    b[0][1] = m_[0][1] * m_[2][3] * m_[3][2] + m_[0][2] * m_[2][1] * m_[3][3] + m_[0][3] * m_[2][2] * m_[3][1] - m_[0][1] * m_[2][2] * m_[3][3] - m_[0][2] * m_[2][3] * m_[3][1] - m_[0][3] * m_[2][1] * m_[3][2];
    b[0][2] = m_[0][1] * m_[1][2] * m_[3][3] + m_[0][2] * m_[1][3] * m_[3][1] + m_[0][3] * m_[1][1] * m_[3][2] - m_[0][1] * m_[1][3] * m_[3][2] - m_[0][2] * m_[1][1] * m_[3][3] - m_[0][3] * m_[1][2] * m_[3][1];
    b[0][3] = m_[0][1] * m_[1][3] * m_[2][2] + m_[0][2] * m_[1][1] * m_[2][3] + m_[0][3] * m_[1][2] * m_[2][1] - m_[0][1] * m_[1][2] * m_[2][3] - m_[0][2] * m_[1][3] * m_[2][1] - m_[0][3] * m_[1][1] * m_[2][2];
    b[1][0] = m_[1][0] * m_[2][3] * m_[3][2] + m_[1][2] * m_[2][0] * m_[3][3] + m_[1][3] * m_[2][2] * m_[3][0] - m_[1][0] * m_[2][2] * m_[3][3] - m_[1][2] * m_[2][3] * m_[3][0] - m_[1][3] * m_[2][0] * m_[3][2];
    b[1][1] = m_[0][0] * m_[2][2] * m_[3][3] + m_[0][2] * m_[2][3] * m_[3][0] + m_[0][3] * m_[2][0] * m_[3][2] - m_[0][0] * m_[2][3] * m_[3][2] - m_[0][2] * m_[2][0] * m_[3][3] - m_[0][3] * m_[2][2] * m_[3][0];
    b[1][2] = m_[0][0] * m_[1][3] * m_[3][2] + m_[0][2] * m_[1][0] * m_[3][3] + m_[0][3] * m_[1][2] * m_[3][0] - m_[0][0] * m_[1][2] * m_[3][3] - m_[0][2] * m_[1][3] * m_[3][0] - m_[0][3] * m_[1][0] * m_[3][2];
    b[1][3] = m_[0][0] * m_[1][2] * m_[2][3] + m_[0][2] * m_[1][3] * m_[2][0] + m_[0][3] * m_[1][0] * m_[2][2] - m_[0][0] * m_[1][3] * m_[2][2] - m_[0][2] * m_[1][0] * m_[2][3] - m_[0][3] * m_[1][2] * m_[2][0];
    b[2][0] = m_[1][0] * m_[2][1] * m_[3][3] + m_[1][1] * m_[2][3] * m_[3][0] + m_[1][3] * m_[2][0] * m_[3][1] - m_[1][0] * m_[2][3] * m_[3][1] - m_[1][1] * m_[2][0] * m_[3][3] - m_[1][3] * m_[2][1] * m_[3][0];
    b[2][1] = m_[0][0] * m_[2][3] * m_[3][1] + m_[0][1] * m_[2][0] * m_[3][3] + m_[0][3] * m_[2][1] * m_[3][0] - m_[0][0] * m_[2][1] * m_[3][3] - m_[0][1] * m_[2][3] * m_[3][0] - m_[0][3] * m_[2][0] * m_[3][1];
    b[2][2] = m_[0][0] * m_[1][1] * m_[3][3] + m_[0][1] * m_[1][3] * m_[3][0] + m_[0][3] * m_[1][0] * m_[3][1] - m_[0][0] * m_[1][3] * m_[3][1] - m_[0][1] * m_[1][0] * m_[3][3] - m_[0][3] * m_[1][1] * m_[3][0];
    b[2][3] = m_[0][0] * m_[1][3] * m_[2][1] + m_[0][1] * m_[1][0] * m_[2][3] + m_[0][3] * m_[1][1] * m_[2][0] - m_[0][0] * m_[1][1] * m_[2][3] - m_[0][1] * m_[1][3] * m_[2][0] - m_[0][3] * m_[1][0] * m_[2][1];
    b[3][0] = m_[1][0] * m_[2][2] * m_[3][1] + m_[1][1] * m_[2][0] * m_[3][2] + m_[1][2] * m_[2][1] * m_[3][0] - m_[1][0] * m_[2][1] * m_[3][2] - m_[1][1] * m_[2][2] * m_[3][0] - m_[1][2] * m_[2][0] * m_[3][1];
    b[3][1] = m_[0][0] * m_[2][1] * m_[3][2] + m_[0][1] * m_[2][2] * m_[3][0] + m_[0][2] * m_[2][0] * m_[3][1] - m_[0][0] * m_[2][2] * m_[3][1] - m_[0][1] * m_[2][0] * m_[3][2] - m_[0][2] * m_[2][1] * m_[3][0];
    b[3][2] = m_[0][0] * m_[1][2] * m_[3][1] + m_[0][1] * m_[1][0] * m_[3][2] + m_[0][2] * m_[1][1] * m_[3][0] - m_[0][0] * m_[1][1] * m_[3][2] - m_[0][1] * m_[1][2] * m_[3][0] - m_[0][2] * m_[1][0] * m_[3][1];
    b[3][3] = m_[0][0] * m_[1][1] * m_[2][2] + m_[0][1] * m_[1][2] * m_[2][0] + m_[0][2] * m_[1][0] * m_[2][1] - m_[0][0] * m_[1][2] * m_[2][1] - m_[0][1] * m_[1][0] * m_[2][2] - m_[0][2] * m_[1][1] * m_[2][0];
    for(int i = 0;i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            m_[i][j] = b[i][j]/det;
        }
    }
}

void Matrix4f::copy_3x3(Matrix4f param)
{
    m_[0][0] = param.get(0, 0);
    m_[1][0] = param.get(1, 0);
    m_[2][0] = param.get(2, 0);
    m_[0][1] = param.get(0, 1);
    m_[1][1] = param.get(1, 1);
    m_[2][1] = param.get(2, 1);
    m_[0][2] = param.get(0, 2);
    m_[1][2] = param.get(1, 2);
    m_[2][2] = param.get(2, 2);
}

void Matrix4f::initScaleTransform(float scaleX, float scaleY, float scaleZ)
{
    m_[0][0] = scaleX; m_[0][1] = 0.0f;   m_[0][2] = 0.0f;   m_[0][3] = 0.0f;
    m_[1][0] = 0.0f;   m_[1][1] = scaleY; m_[1][2] = 0.0f;   m_[1][3] = 0.0f;
    m_[2][0] = 0.0f;   m_[2][1] = 0.0f;   m_[2][2] = scaleZ; m_[2][3] = 0.0f;
    m_[3][0] = 0.0f;   m_[3][1] = 0.0f;   m_[3][2] = 0.0f;   m_[3][3] = 1.0f;
}

void Matrix4f::initRotateTransform(float rotateX, float rotateY, float rotateZ)
{
    Matrix4f rx, ry, rz;

    const float x = toRadian(rotateX);
    const float y = toRadian(rotateY);
    const float z = toRadian(rotateZ);

    rx.m_[0][0] = 1.0f; rx.m_[0][1] = 0.0f; rx.m_[0][2] = 0.0f; rx.m_[0][3] = 0.0f;
    rx.m_[1][0] = 0.0f; rx.m_[1][1] = cosf(x); rx.m_[1][2] = -sinf(x); rx.m_[1][3] = 0.0f;
    rx.m_[2][0] = 0.0f; rx.m_[2][1] = sinf(x); rx.m_[2][2] = cosf(x); rx.m_[2][3] = 0.0f;
    rx.m_[3][0] = 0.0f; rx.m_[3][1] = 0.0f; rx.m_[3][2] = 0.0f; rx.m_[3][3] = 1.0f;

    ry.m_[0][0] = cosf(y); ry.m_[0][1] = 0.0f; ry.m_[0][2] = -sinf(y); ry.m_[0][3] = 0.0f;
    ry.m_[1][0] = 0.0f; ry.m_[1][1] = 1.0f; ry.m_[1][2] = 0.0f; ry.m_[1][3] = 0.0f;
    ry.m_[2][0] = sinf(y); ry.m_[2][1] = 0.0f; ry.m_[2][2] = cosf(y); ry.m_[2][3] = 0.0f;
    ry.m_[3][0] = 0.0f; ry.m_[3][1] = 0.0f; ry.m_[3][2] = 0.0f; ry.m_[3][3] = 1.0f;

    rz.m_[0][0] = cosf(z); rz.m_[0][1] = -sinf(z); rz.m_[0][2] = 0.0f; rz.m_[0][3] = 0.0f;
    rz.m_[1][0] = sinf(z); rz.m_[1][1] = cosf(z); rz.m_[1][2] = 0.0f; rz.m_[1][3] = 0.0f;
    rz.m_[2][0] = 0.0f; rz.m_[2][1] = 0.0f; rz.m_[2][2] = 1.0f; rz.m_[2][3] = 0.0f;
    rz.m_[3][0] = 0.0f; rz.m_[3][1] = 0.0f; rz.m_[3][2] = 0.0f; rz.m_[3][3] = 1.0f;

    *this = rz * ry * rx;
}

/*
void Matrix4f::initRotateTransform(const Quaternion& quat)
{
    float yy2 = 2.0f * quat.y * quat.y;
    float xy2 = 2.0f * quat.x * quat.y;
    float xz2 = 2.0f * quat.x * quat.z;
    float yz2 = 2.0f * quat.y * quat.z;
    float zz2 = 2.0f * quat.z * quat.z;
    float wz2 = 2.0f * quat.w * quat.z;
    float wy2 = 2.0f * quat.w * quat.y;
    float wx2 = 2.0f * quat.w * quat.x;
    float xx2 = 2.0f * quat.x * quat.x;
    m_[0][0] = -yy2 - zz2 + 1.0f;
    m_[0][1] = xy2 + wz2;
    m_[0][2] = xz2 - wy2;
    m_[0][3] = 0;
    m_[1][0] = xy2 - wz2;
    m_[1][1] = -xx2 - zz2 + 1.0f;
    m_[1][2] = yz2 + wx2;
    m_[1][3] = 0;
    m_[2][0] = xz2 + wy2;
    m_[2][1] = yz2 - wx2;
    m_[2][2] = -xx2 - yy2 + 1.0f;
    m_[2][3] = 0.0f;
    m_[3][0] = m_[3][1] = m_[3][2] = 0;
    m_[3][3] = 1.0f;
}
*/

void Matrix4f::initTranslationTransform(float x, float y, float z)
{
    m_[0][0] = 1.0f; m_[0][1] = 0.0f; m_[0][2] = 0.0f; m_[0][3] = x;
    m_[1][0] = 0.0f; m_[1][1] = 1.0f; m_[1][2] = 0.0f; m_[1][3] = y;
    m_[2][0] = 0.0f; m_[2][1] = 0.0f; m_[2][2] = 1.0f; m_[2][3] = z;
    m_[3][0] = 0.0f; m_[3][1] = 0.0f; m_[3][2] = 0.0f; m_[3][3] = 1.0f;
}

void Matrix4f::initCameraTransform(Vector3f & target, Vector3f& up)
{
    Vector3f n = target;
    n.normalize();
    Vector3f u = up;
    u.normalize();
    u = u.crossProduct(n);
    Vector3f v = n.crossProduct(u);

    m_[0][0] = u.x();   m_[0][1] = u.y();   m_[0][2] = u.z();   m_[0][3] = 0.0f;
    m_[1][0] = v.x();   m_[1][1] = v.y();   m_[1][2] = v.z();   m_[1][3] = 0.0f;
    m_[2][0] = n.x();   m_[2][1] = n.y();   m_[2][2] = n.z();   m_[2][3] = 0.0f;
    m_[3][0] = 0.0f;    m_[3][1] = 0.0f;    m_[3][2] = 0.0f;    m_[3][3] = 1.0f;
}

void Matrix4f::initPersProjTransform(const PersProjInfo& p)
{
    const float ar = p.width_ / p.height_;
    const float zRange = p.zNear_ - p.zFar_;
    const float tanHalfFOV = tanf(toRadian(p.fov_ / 2.0f));

    m_[0][0] = 1.0f / (tanHalfFOV * ar); m_[0][1] = 0.0f;              m_[0][2] = 0.0f;                         m_[0][3] = 0.0;
    m_[1][0] = 0.0f;                     m_[1][1] = 1.0f / tanHalfFOV; m_[1][2] = 0.0f;                         m_[1][3] = 0.0;
    m_[2][0] = 0.0f;                     m_[2][1] = 0.0f;              m_[2][2] = (-p.zNear_ - p.zFar_) / zRange; m_[2][3] = 2.0f*p.zFar_*p.zNear_ / zRange;
    m_[3][0] = 0.0f;                     m_[3][1] = 0.0f;              m_[3][2] = 1.0f;                         m_[3][3] = 0.0;
}

void Matrix4f::initOrthoProjTransform(const OrthoProjInfo& p)
{
    float l = p.l_;
    float r = p.r_;
    float b = p.b_;
    float t = p.t_;
    float n = p.n_;
    float f = p.f_;

    m_[0][0] = 2.0f / (r - l); m_[0][1] = 0.0f;         m_[0][2] = 0.0f;         m_[0][3] = -(r + l) / (r - l);
    m_[1][0] = 0.0f;         m_[1][1] = 2.0f / (t - b); m_[1][2] = 0.0f;         m_[1][3] = -(t + b) / (t - b);
    m_[2][0] = 0.0f;         m_[2][1] = 0.0f;         m_[2][2] = 2.0f / (f - n); m_[2][3] = -(f + n) / (f - n);
    m_[3][0] = 0.0f;         m_[3][1] = 0.0f;         m_[3][2] = 0.0f;         m_[3][3] = 1.0;
}



