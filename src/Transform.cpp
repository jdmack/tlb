#include "Transform.h"
#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "math/Matrix4f.h"
#include "Game.h"
#include "gfx/Renderer.h"

#include <iostream>

/* NOTES
 * At some point could trade space for runtime by having fields for scale, translation,
 * and rotation matrices, and dirty flags for each.
 */

Transform::Transform()
{
    scale_      = Vector3f(1.0f, 1.0f, 1.0f);
    translation_   = Vector3f(0.0f, 0.0f, 0.0f);
    rotation_ = Vector3f(0.0f, 0.0f, 0.0f);

    dirty_ = true;
}

void Transform::scale(float s)
{
    scale(s, s, s);
    dirty_ = true;
}
 
void Transform::scale(const Vector3f & s)
{
    scale(s.x(), s.y(), s.z());
    dirty_ = true;
}

void Transform::scale(float scaleX, float scaleY, float scaleZ)
{
    scale_.setX(scaleX);
    scale_.setY(scaleY);
    scale_.setZ(scaleZ);
    dirty_ = true;
}

void Transform::scale(int which, float scale)
{
    scale_.set(which, scale);
    dirty_ = true;
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
    dirty_ = true;
}
 
void Transform::translate(float x, float y, float z)
{
    translation_.setX(x);
    translation_.setY(y);
    translation_.setZ(z);
    dirty_ = true;
}
 
void Transform::translate(const Vector3f & translation)
{
    translation_ = translation;
    dirty_ = true;
}

void Transform::translate(int which, float value)
{
    translation_.set(which, value);
    dirty_ = true;
}

void Transform::translateRel(float x, float y, float z)
{
    if(x != 0) {
        translation_.setX(translation_.x() + x);
    }
    if(y != 0) {
        translation_.setY(translation_.y() + y);
    }
    if(z != 0) {
        translation_.setZ(translation_.z() + z);
    }
    dirty_ = true;
}

void Transform::rotate(float rotateX, float rotateY, float rotateZ)
{
    rotation_.setX(rotateX);
    rotation_.setY(rotateY);
    rotation_.setZ(rotateZ);
    dirty_ = true;
}
 
void Transform::rotate(const Vector3f & r)
{
    rotate(r.x(), r.y(), r.z());
    dirty_ = true;
}

void Transform::rotate(int which, float value)
{
    rotation_.set(which, value);
    dirty_ = true;
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
    dirty_ = true;
}

//void Transform::orient(const Orientation & o)
//{
//    scale_      = o.scale_;
//    translation_   = o.translation_;
//    rotation_ = o.rotation_;
//}

const Matrix4f& Transform::worldTrans()
{
    if(dirty_) {
        Matrix4f scaleTrans, rotateTrans, translationTrans;

        scaleTrans.initScaleTransform(scale_.x(), scale_.y(), scale_.z());
        rotateTrans.initRotateTransform(rotation_.x(), rotation_.y(), rotation_.z());
        translationTrans.initTranslationTransform(translation_.x(), translation_.y(), translation_.z());
        worldTrans_ = translationTrans * rotateTrans * scaleTrans;

        dirty_ = false;
    }

    return worldTrans_;
}

