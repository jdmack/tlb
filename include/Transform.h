#ifndef TLB_TRANSFORM_H_
#define TLB_TRANSFORM_H_

#include "gfx/Camera.h"
#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "math/Matrix4f.h"

class Matrix4f;

struct Orientation
{
    Vector3f scale_;
    Vector3f rotation_;
    Vector3f position_;       
    
    Orientation()
    {
        scale_    = Vector3f(1.0f, 1.0f, 1.0f);
        rotation_ = Vector3f(0.0f, 0.0f, 0.0f);
        position_ = Vector3f(0.0f, 0.0f, 0.0f);
    }
};

/*
    P - Projection - Perspective Projection
    V - View - Camera
    W - World - Translate, Rotate, Scale
*/

class Transform
{
    private:
        Vector3f scale_;
        Vector3f worldPos_;
        Vector3f rotateInfo_;

        OrthoProjInfo orthoProjInfo_;

        Matrix4f WVPtransformation_;
        Matrix4f VPtransformation_;
        Matrix4f WPtransformation_;
        Matrix4f WVTransform_;
        Matrix4f Wtransformation_;
        Matrix4f viewTransform_;
        Matrix4f projTransformation_; // TODO(2016-04-24/JM): Probably want this part of the renderer

    public:
        Transform();

        void scale(float s);
        void scale(Vector3f & scale);
        void scale(float scaleX, float scaleY, float scaleZ);
        void scale(int which, float scale);
        void worldPos(float x, float y, float z);
        void worldPos(Vector3f & position);
        void rotate(float rotateX, float rotateY, float rotateZ);
        void rotate(Vector3f & rotation);
        void setPerspectiveProj(const PersProjInfo& p);
        void orient(const Orientation & o);

        const Matrix4f & getWPTrans();
        const Matrix4f & getWVTrans();
        const Matrix4f & getVPTrans();
        //const Matrix4f & getWVPTrans();
        Matrix4f & getWVPTrans();
        const Matrix4f & getWVOrthoPTrans();
        const Matrix4f & getWorldTrans();
        const Matrix4f & getViewTrans();
        const Matrix4f & getProjTrans();
};

#endif

