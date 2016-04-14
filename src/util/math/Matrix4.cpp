#include <iostream> 
#include <iomanip>
#include <math.h>

#include "util/math/Matrix4.h"

// Note: Matrix is stored row-major.

Matrix4::Matrix4()
{
    for(int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m_[row][col] = 0;
        }
    }
}

Matrix4::Matrix4(bool identity)
{
    if(identity) this->identity();
}

Matrix4::Matrix4(const Matrix4 &param)
{
    for(int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m_[row][col] = param.get(row, col);
        }
    }
} 

// Constructor with 16 parameters to set the values of the matrix
Matrix4::Matrix4(float m00, float m01, float m02, float m03,
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
float Matrix4::get(int x, int y) const
{
    return m_[x][y];
}

void Matrix4::set(int x, int y, float value)
{
    m_[x][y] = value;
}

void Matrix4::set(Matrix4 param)
{
    for(int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m_[row][col] = param.get(row,col);
        }
    }
}
// Multiply (matrix-times-matrix)
Matrix4 Matrix4::multiply(Matrix4 param)
{
    Matrix4 result;

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
Vector4 Matrix4::multiply(Vector4 param)
{
    Vector4 result;
    transpose();
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.set(row, result.get(row) + m_[row][col] * param.get(col));
        }
    }
    transpose();
    return result;
}

Matrix4 Matrix4::operator*(Matrix4 & param)
{
    return multiply(param);
}

Vector4 Matrix4::operator*(Vector4 & param)
{
    return multiply(param);
}

// Make a rotation matrix about the x axis
void Matrix4::rotateX(float angle)
{
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians
     Matrix4 param(1,          0,           0, 0,
                   0, cos(angle), -sin(angle), 0,
                   0, sin(angle),  cos(angle), 0,
                   0,          0,           0, 1);
    set(multiply(param));
}

// Make a rotation matrix about the y axis
// angle in degrees
void Matrix4::rotateY(float angle)
{
    angle = (angle / 180.0) * M_PI;  // convert from degrees to radians
    Matrix4 param( cos(angle), 0, sin(angle), 0, 
                             0, 1,          0, 0, 
                   -sin(angle), 0, cos(angle), 0, 
                             0, 0,          0, 1);
    set(multiply(param));
}

// Make a rotation matrix about the z axis
void Matrix4::rotateZ(float angle)
{
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians  
    Matrix4 param(cos(angle), -sin(angle), 0, 0,
                  sin(angle),  cos(angle), 0, 0,
                           0,           0, 1, 0,
                           0,           0, 0, 1);
    set(multiply(param));
}

// Make a rotation matrix about an arbitrary (unit) axis
void Matrix4::rotate(float angle, Vector4 axis)
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

    Matrix4 param(m00, m01, m02, m03,
                  m10, m11, m12, m13,
                  m20, m21, m22, m23,
                  m30, m31, m32, m33);

    set(multiply(param));
}

// Make a non-uniform scaling matrix
void Matrix4::scale(float x, float y, float z)
{
    Matrix4 param(x,0,0,0,
                  0,y,0,0,
                  0,0,z,0,
                  0,0,0,1);

    set(multiply(param));
}

// Make a translation matrix
void Matrix4::translate(float x, float y, float z)
{
    Matrix4 param(1,0,0,x,
                  0,1,0,y,
                  0,0,1,z,
                  0,0,0,1);
    param.transpose();
    set(multiply(param));
}

// Print the matrix (display all 16 matrix components numerically on the screen in a 4x4 array)
void Matrix4::print()
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
void Matrix4::transpose()
{
    Matrix4 temp;
    temp.set(*this);

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            m_[row][col] = temp.get(col, row);
        }
    }
}

float * Matrix4::pointer()
{
    return &m_[0][0];
}

void Matrix4::identity()
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

void Matrix4::invert()
{
    /*
    Matrix4 rotation(m_[0][0], m_[0][1], m_[0][2], 0,
                     m_[1][0], m_[1][1], m_[1][2], 0,
                     m_[2][0], m_[2][1], m_[2][2], 0,
                           0,       0,       0, 1);

    Matrix4 translation(1, 0, 0, -m_[0][3],
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

void Matrix4::copy_3x3(Matrix4 param)
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



