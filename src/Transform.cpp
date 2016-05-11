#include "Transform.h"
#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "math/Matrix4f.h"
#include "Game.h"
#include "gfx/Renderer.h"

#include <iostream>

Transform::Transform()
{
    scale_      = Vector3f(1.0f, 1.0f, 1.0f);
    position_   = Vector3f(0.0f, 0.0f, 0.0f);
    rotation_ = Vector3f(0.0f, 0.0f, 0.0f);
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

void Transform::scale(int which, float scale)
{
    scale_.set(which, scale);
}

void Transform::scaleRel(float scaleX, float scaleY, float scaleZ)
{
    if(scaleX != 0) {
        scale_.setX(scale_.x() * scaleX);
    }
    if(scaleY != 0) {
        scale_.setY(scale_.y() * scaleY);
    }
    if(scaleZ != 0) {
        scale_.setZ(scale_.z() * scaleZ);
    }
}
 
void Transform::setPosition(float x, float y, float z)
{
    position_.setX(x);
    position_.setY(y);
    position_.setZ(z);
}
 
// TODO(2016-04-27/JM): Figure out how to make this argument const Vector3f & position
void Transform::setPosition(Vector3f & position)
{
    position_ = position;
}

void Transform::setPosition(int which, float value)
{
    position_.set(which, value);
}

void Transform::setPositionRel(float x, float y, float z)
{
    if(x != 0) {
        position_.setX(position_.x() + x);
    }
    if(y != 0) {
        position_.setY(position_.y() + y);
    }
    if(z != 0) {
        position_.setZ(position_.z() + z);
    }

}

void Transform::rotate(float rotateX, float rotateY, float rotateZ)
{
    rotation_.setX(rotateX);
    rotation_.setY(rotateY);
    rotation_.setZ(rotateZ);
}
 
// TODO(2016-04-27/JM): Figure out how to make this argument const Vector3f & r
void Transform::rotate(Vector3f & r)
{
    rotate(r.x(), r.y(), r.z());
}

void Transform::rotate(int which, float value)
{
    rotation_.set(which, value);
}

void Transform::rotateRel(float rotateX, float rotateY, float rotateZ)
{
    if(rotateX != 0) {
        rotation_.rotate(rotateX, Vector3f(1.0, 0.0, 0.0));
    }
    if(rotateY != 0) {
        rotation_.rotate(rotateY, Vector3f(0.0, 1.0, 0.0));
    }
    if(rotateZ != 0) {
        rotation_.rotate(rotateZ, Vector3f(0.0, 0.0, 1.0));
    }
}

//void Transform::orient(const Orientation & o)
//{
//    scale_      = o.scale_;
//    position_   = o.position_;
//    rotation_ = o.rotation_;
//}

const Matrix4f& Transform::getTrans()
{
    Matrix4f ScaleTrans, RotateTrans, TranslationTrans;

    ScaleTrans.initScaleTransform(scale_.x(), scale_.y(), scale_.z());
    RotateTrans.initRotateTransform(rotation_.x(), rotation_.y(), rotation_.z());
    TranslationTrans.initTranslationTransform(position_.x(), position_.y(), position_.z());
    transformation_ = TranslationTrans * RotateTrans * ScaleTrans;
    return transformation_;
}

