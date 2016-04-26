#include "Transform.h"
#include "util/math/Vector3.h"
#include "util/math/Vector4.h"
#include "util/math/Matrix4.h"

Transform::Transform()
{
    scale_      = Vector3(1.0f, 1.0f, 1.0f);
    worldPos_   = Vector3(0.0f, 0.0f, 0.0f);
    rotateInfo_ = Vector3(0.0f, 0.0f, 0.0f);
}

void Transform::scale(float s)
{
    scale(s, s, s);
}
 
void Transform::scale(Vector3 s)
{
    scale(s.x(), s.y(), s.z());
}
 
void Transform::scale(float scaleX, float scaleY, float scaleZ)
{
    scale_.setX(scaleX);
    scale_.setY(scaleY);
    scale_.setZ(scaleZ);
}

void Transform::worldPos(float x, float y, float z)
{
    worldPos_.setX(x);
    worldPos_.setY(y);
    worldPos_.setZ(z);
}
 
void Transform::worldPos(Vector3 position)
{
    worldPos_ = position;
}

void Transform::rotate(float rotateX, float rotateY, float rotateZ)
{
    rotateInfo_.setX(rotateX);
    rotateInfo_.setY(rotateY);
    rotateInfo_.setZ(rotateZ);
}
 
void Transform::rotate(Vector3 r)
{
    rotate(r.x(), r.y(), r.z());
}

void Transform::setPerspectiveProj(const PersProjInfo & p)
{
    persProjInfo_ = p;
}

//void Transform::setCamera(const Vector3 & position, const Vector3 & target, const Vector3 & up)
//{
//    camera_.position = position;
//    camera_.target   = target;
//    camera_.up       = up;
//}

//void Transform::setCamera(const Camera & camera)
//{
//    setCamera(camera.position(), camera.target(), camera.up());
//}
 
/*
void Transform::orient(const Orientation & o)
{
    scale_      = o.scale_;
    worldPos_   = o.position_;
    rotateInfo_ = o.rotation_;
}
*/

const Matrix4& Transform::getProjTrans() 
{
    //projTransformation_.initPersProjTransform(persProjInfo_);
    return projTransformation_;
}

const Matrix4& Transform::getVPTrans()
{
    getViewTrans();
    getProjTrans();
       
    VPtransformation_ = projTransformation_ * Vtransformation_;
    return VPtransformation_;
}

const Matrix4& Transform::getWorldTrans()
{
    Matrix4 ScaleTrans, RotateTrans, TranslationTrans;

    //ScaleTrans.initScaleTransform(scale_.x, scale_.y, scale_.z);
    //RotateTrans.initRotateTransform(rotateInfo_.x, rotateInfo_.y, rotateInfo_.z);
    //TranslationTrans.initTranslationTransform(worldPos_.x, worldPos_.y, worldPos_.z);
    Wtransformation_ = TranslationTrans * RotateTrans * ScaleTrans;
    return Wtransformation_;
}

const Matrix4& Transform::getViewTrans()
{
    Matrix4 CameraTranslationTrans, CameraRotateTrans;

    //CameraTranslationTrans.initTranslationTransform(-camera.Pos.x, -camera.Pos.y, -camera.Pos.z);
    //CameraRotateTrans.initCameraTransform(camera.Target, camera.Up);
    
    Vtransformation_ = CameraRotateTrans * CameraTranslationTrans;

    return Vtransformation_;
}

const Matrix4& Transform::getWVPTrans()
{
    getWorldTrans();
    getVPTrans();

    WVPtransformation_ = VPtransformation_ * Wtransformation_;
    return WVPtransformation_;
}

const Matrix4& Transform::getWVOrthoPTrans()
{
    getWorldTrans();
    getViewTrans();

    Matrix4 p;
    //p.initOrthoProjTransform(persProjInfo_);
    
    //WVPtransformation_ = p * Vtransformation_ * Wtransformation_;
    return WVPtransformation_;
}


const Matrix4& Transform::getWVTrans()
{
	getWorldTrans();
    getViewTrans();
	
	WVtransformation_ = Vtransformation_ * Wtransformation_;
	return WVtransformation_;
}


const Matrix4& Transform::getWPTrans()
{
	Matrix4 PersProjTrans;

	getWorldTrans();
	//PersProjTrans.initPersProjTransform(persProjInfo_);

	//WPtransformation_ = PersProjTrans * Wtransformation_;
	return WPtransformation_;
}

