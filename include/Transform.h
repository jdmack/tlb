#ifndef TLB_TRANSFORM_H_
#define TLB_TRANSFORM_H_

#include "math/Vector3f.h"
#include "math/Matrix4f.h"

class Matrix4f;

class Transform
{
    private:
        bool dirty_;

        Vector3f scale_;
        Vector3f translation_;
        Vector3f rotation_;

        Matrix4f worldTrans_;

    public:
        Transform();

        void scale(float s);
        void scale(const Vector3f & scale);
        void scale(float scaleX, float scaleY, float scaleZ);
        void scale(int which, float scale);
        void scaleRel(float scaleX, float scaleY, float scaleZ);

        void translate(float x, float y, float z);
        void translate(const Vector3f & translation);
        void translate(int which, float value);
        void translateRel(float x, float y, float z);

        void rotate(float rotateX, float rotateY, float rotateZ);
        void rotate(const Vector3f & rotation);
        void rotate(int which, float value);
        void rotateRel(float rotateX, float rotateY, float rotateZ);

        const Matrix4f & worldTrans();

        //void orient(const Orientation & o);
};

//struct Orientation
//{
//    Vector3f scale_;
//    Vector3f rotation_;
//    Vector3f translation_;       
    
//    Orientation()
//    {
//        scale_    = Vector3f(1.0f, 1.0f, 1.0f);
//        rotation_ = Vector3f(0.0f, 0.0f, 0.0f);
//        translation_ = Vector3f(0.0f, 0.0f, 0.0f);
//    }
//};

#endif

