#ifndef TLB_TRANSFORM_H_
#define TLB_TRANSFORM_H_

#include "util/math/vector3.h"
#include "util/math/vector3.h"
#include "util/math/vector3.h"
//#include "ogldev_camera.h"

struct Orientation
{
    Vector3 scale_;
    Vector3 rotation_;
    Vector3 position_;       
    
    Orientation()
    {
        scale_    = Vector3(1.0f, 1.0f, 1.0f);
        rotation_ = Vector3(0.0f, 0.0f, 0.0f);
        position_ = Vector3(0.0f, 0.0f, 0.0f);
    }
};

// TODO(2016-04-24/JM): Possibly move this struct somewhere else
struct PersProjInfo
{
    float fov_;
    float width_;
    float height_;
    float zNear_;
    float zFar_;

};


class Transform
{
   private:
       Vector3 scale_;
       Vector3 worldPos_;
       Vector3 rotateInfo_;

       PersProjInfo persProjInfo_;

       struct {
           Vector3 position;
           Vector3 target;
           Vector3 up;
       } camera_;

       Matrix4 WVPtransformation_;
       Matrix4 VPtransformation_;
       Matrix4 WPtransformation_;
       Matrix4 WVtransformation_;
       Matrix4 Wtransformation_;
       Matrix4 Vtransformation_;
       Matrix4 projTransformation_; // TODO(2016-04-24/JM): Probably want this part of the renderer

   public:
       Transform();

       void scale(float s);
       void scale(const Vector3 & scale);
       void scale(float scaleX, float scaleY, float scaleZ);
       void worldPos(float x, float y, float z);
       void worldPos(const Vector3 & position);
       void rotate(float rotateX, float rotateY, float rotateZ);
       void rotate(const Vector3 & rotation);
       void setPerspectiveProj(const PersProjInfo& p);
       //void setCamera(const Vector3 & position, const Vector3 & target, const Vector3 & up);
       //void setCamera(const Camera & camera);
       void orient(const Orientation & o);

       const Matrix4 & getWPTrans();
       const Matrix4 & getWVTrans();
       const Matrix4 & getVPTrans();
       const Matrix4 & getWVPTrans();
       const Matrix4 & getWVOrthoPTrans();
       const Matrix4 & getWorldTrans();
       const Matrix4 & getViewTrans();
       const Matrix4 & getProjTrans();

       


};

#endif

