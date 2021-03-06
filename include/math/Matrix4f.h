#ifndef TLB_UTIL_MATH_MATRIX4_H_
#define TLB_UTIL_MATH_MATRIX4_H_

#include "math/Vector3f.h"
#include "gfx/Projection.h"

class Vector3f;

class Matrix4f
{
    private:
        float m_[4][4];   // matrix elements

    public:
        // constructors
        Matrix4f();
        Matrix4f(bool identity);
        Matrix4f(const Matrix4f &param);
        // Constructor with 16 parameters to set the values of the matrix
        Matrix4f(float, float, float, float,
                float, float, float, float,
                float, float, float, float,
                float, float, float, float);

        // 'get(x,y)' function to read any matrix element
        float get(int x, int y) const;

        void set(int x, int y, float value);
        void set(Matrix4f param);

        // Copy assignment operator
        Matrix4f & operator=(Matrix4f m);

        // Multiply (matrix-times-matrix)
        Matrix4f multiply(Matrix4f param);

        // Multiply (matrix-times-vector)
        Vector4f multiply(Vector4f param);

        Matrix4f operator*(Matrix4f & param);
        Vector4f operator*(Vector4f & param);

        // Make a rotation matrix about the x axis
        void rotateX(float angle);

        // Make a rotation matrix about the y axis
        void rotateY(float angle);

        // Make a rotation matrix about the z axis
        void rotateZ(float angle);

        // Make a rotation matrix about an arbitrary (unit) axis
        void rotate(float angle, Vector4f axis);

        // Make a non-uniform scaling matrix
        void scale(float x, float y, float z);

        // Make a translation matrix
        void translate(float x, float y, float z);

        // Transpose the matrix
        void transpose();

        const float * pointer() const;
        void identity();

        float determinant();
        void invert();

        void copy_3x3(Matrix4f param);

        // TODO(2016-05-14/JM): Decide whether to move these functions or not
        void initScaleTransform(float scaleX, float scaleY, float scaleZ);
        void initRotateTransform(float rotateX, float rotateY, float rotateZ);
        //void initRotateTransform(const Quaternion& quat);
        void initTranslationTransform(float x, float y, float z);
        void initOrthoProjTransform(const OrthoProjInfo& p);

        friend std::ostream & operator<<(std::ostream & os, const Matrix4f & v);


};

#endif
