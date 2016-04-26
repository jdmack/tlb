#ifndef TLB_UTIL_MATH_MATRIX4_H_
#define TLB_UTIL_MATH_MATRIX4_H_

//#include "util/math/Vector4.h"
//#include "util/math/Vector3.h"
//#include "Transform.h"

#define M_PI 3.14159265358979323846

#define toRadian(x) (float)(((x) * M_PI / 180.0f))
#define toDegree(x) (float)(((x) * 180.0f / M_PI))

class Vector3;
class Vector4;

class Matrix4
{
    private:
        float m_[4][4];   // matrix elements

    public:
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

        // Copy assignment operator
        Matrix4 & operator=(Matrix4 m);

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

        // TODO(2016-04-24/JM): Possibly move this function somewhere else, probably want a perspective projection as part of the renderer
        //void initScaleTransform(float scaleX, float scaleY, float scaleZ);
        //void initRotateTransform(float rotateX, float rotateY, float rotateZ);
        //void initRotateTransform(const Quaternion& quat);
        //void initTranslationTransform(float x, float y, float z);
        //void initCameraTransform(const Vector3f& Target, const Vector3f& Up);
        //void initPersProjTransform(const PersProjInfo& p);
        //void initOrthoProjTransform(const OrthoProjInfo& p);

};

#endif
