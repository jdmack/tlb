#ifndef TLB_TRANSFORM_H_
#define TLB_TRANSFORM_H_

#include "gfx/Camera.h"
#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "math/Matrix4f.h"

class Matrix4f;

//struct Orientation
//{
//    Vector3f scale_;
//    Vector3f rotation_;
//    Vector3f position_;       
    
//    Orientation()
//    {
//        scale_    = Vector3f(1.0f, 1.0f, 1.0f);
//        rotation_ = Vector3f(0.0f, 0.0f, 0.0f);
//        position_ = Vector3f(0.0f, 0.0f, 0.0f);
//    }
//};

/*
    P - Projection - Perspective Projection
    V - View - Camera
    W - World - Translate, Rotate, Scale
*/

class Transform
{
    private:
        Vector3f scale_;
        Vector3f position_;
        Vector3f rotation_;

        Matrix4f transformation_;

    public:
        Transform();

        void scale(float s);
        void scale(Vector3f & scale);
        void scale(float scaleX, float scaleY, float scaleZ);
        void scale(int which, float scale);

        void setPosition(float x, float y, float z);
        void setPosition(Vector3f & position);

        void rotate(float rotateX, float rotateY, float rotateZ);
        void rotate(Vector3f & rotation);
        //void orient(const Orientation & o);

        const Matrix4f & getTrans();
};

#endif

