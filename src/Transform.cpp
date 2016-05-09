#include "Transform.h"
#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "math/Matrix4f.h"
#include "Game.h"
#include "gfx/Renderer.h"

#include <iostream>

// TODO(2016-04-27/JM): Fix local variable names in this class (some use improperly capitalized names from old source)

Transform::Transform()
{
    scale_      = Vector3f(1.0f, 1.0f, 1.0f);
    worldPos_   = Vector3f(0.0f, 0.0f, 0.0f);
    rotateInfo_ = Vector3f(0.0f, 0.0f, 0.0f);
}

void Transform::scale(float s)
{
    scale(s, s, s);
}
 
// TODO(2016-04-27/JM): Figure out how to make this argument const Vector3f & s
void Transform::scale(Vector3f & s)
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
 
// TODO(2016-04-27/JM): Figure out how to make this argument const Vector3f & position
void Transform::worldPos(Vector3f & position)
{
    worldPos_ = position;
}

void Transform::rotate(float rotateX, float rotateY, float rotateZ)
{
    rotateInfo_.setX(rotateX);
    rotateInfo_.setY(rotateY);
    rotateInfo_.setZ(rotateZ);
}
 
// TODO(2016-04-27/JM): Figure out how to make this argument const Vector3f & r
void Transform::rotate(Vector3f & r)
{
    rotate(r.x(), r.y(), r.z());
}

void Transform::setPerspectiveProj(const PersProjInfo & p)
{
    //persProjInfo_ = p;
}

void Transform::orient(const Orientation & o)
{
    scale_      = o.scale_;
    worldPos_   = o.position_;
    rotateInfo_ = o.rotation_;
}

const Matrix4f& Transform::getProjTrans() 
{
    projTransformation_.initPersProjTransform(Game::instance()->renderer()->camera()->persProjInfo());
    return projTransformation_;
}

const Matrix4f& Transform::getVPTrans()
{
    getViewTrans();
    getProjTrans();
       
    VPtransformation_ = projTransformation_ * viewTransform_;
    return VPtransformation_;
}

const Matrix4f& Transform::getWorldTrans()
{
    Matrix4f ScaleTrans, RotateTrans, TranslationTrans;

    ScaleTrans.initScaleTransform(scale_.x(), scale_.y(), scale_.z());
    RotateTrans.initRotateTransform(rotateInfo_.x(), rotateInfo_.y(), rotateInfo_.z());
    TranslationTrans.initTranslationTransform(worldPos_.x(), worldPos_.y(), worldPos_.z());
    Wtransformation_ = TranslationTrans * RotateTrans * ScaleTrans;
    //std::cout << "World: " << std::endl;
    //Wtransformation_.print();
    return Wtransformation_;
}

const Matrix4f& Transform::getViewTrans()
{
    viewTransform_ = Game::instance()->renderer()->camera()->view();
    

    return viewTransform_;
}

//const Matrix4f& Transform::getWVPTrans()
Matrix4f& Transform::getWVPTrans()
{
    getWorldTrans();
    getVPTrans();

    WVPtransformation_ = VPtransformation_ * Wtransformation_;
    return WVPtransformation_;
}

const Matrix4f& Transform::getWVOrthoPTrans()
{
    getWorldTrans();
    getViewTrans();

    Matrix4f p;
    p.initOrthoProjTransform(orthoProjInfo_);
    
    WVPtransformation_ = p * viewTransform_ * Wtransformation_;
    return WVPtransformation_;
}


const Matrix4f& Transform::getWVTrans()
{
	getWorldTrans();
    getViewTrans();
	
	WVTransform_ = viewTransform_ * Wtransformation_;
	return WVTransform_;
}


const Matrix4f& Transform::getWPTrans()
{
	Matrix4f PersProjTrans;

	getWorldTrans();
	PersProjTrans.initPersProjTransform(Game::instance()->renderer()->camera()->persProjInfo());

	WPtransformation_ = PersProjTrans * Wtransformation_;
	return WPtransformation_;
}

