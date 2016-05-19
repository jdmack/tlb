#include <iostream>
#include <cmath>
#include "gfx/Camera.h"
#include "math/Math.h"
#include "util/Logger.h"

const static float kMaxVAngle = 90.0f;
const static float kMinVAngle = -90.0f;

Camera::Camera(int windowWidth, int windowHeight)
{
    //position_ = Vector3f(0.0f, 0.0f, 1.0f);
    //target_   = Vector3f(0.0f, 0.0f, 1.0f);
    //up_       = Vector3f(0.0f, 1.0f, 0.0f);
    position_ = Vector3f(11.0f, 13.0f, 0.0f);
    target_   = Vector3f(0.0f, 0.9f, -0.4f);
    up_       = Vector3f(0.0f, 0.4f, 0.9f);

    target_.normalize();

    updateView();

    fov_ = 60.0f;
    width_ = windowWidth;
    height_ = windowHeight;
    zNear_ = 0.1f;
    zFar_ = 100.0f;

    updateView();
    updateProjection();

    init();
}

Camera::Camera(int windowWidth, int windowHeight, const Vector3f & position, const Vector3f & target, const Vector3f& up)
{
    position_ = position;
    target_ = target;
    up_ = up;

    target_.normalize();
    up_.normalize();

    updateView();

    fov_ = 60.0f;
    width_ = windowWidth;
    height_ = windowHeight;
    zNear_ = 0.1f;
    zFar_ = 100.0f;

    init();
}


void Camera::init()
{
    // This function extracts the angles from the target vector
    Vector3f hTarget(target_.x(), 0.0, target_.z());
    hTarget.normalize();
    
    if(hTarget.z() >= 0.0f) {
        if(hTarget.x() >= 0.0f) {
            angleH_ = 360.0f - toDegree(asin(hTarget.z()));
        }
        else {
            angleH_ = 180.0f + toDegree(asin(hTarget.z()));
        }
    }
    else {
        if(hTarget.x() >= 0.0f) {
            angleH_ = toDegree(asin(-hTarget.z()));
        }
        else {
            angleH_ = 90.0f + toDegree(asin(-hTarget.z()));
        }
    }
    
    angleV_ = -toDegree(asin(target_.y()));
}

void Camera::update()
{
    const Vector3f vAxis(0.0f, 1.0f, 0.0f);

    // rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);

    View.rotate(angleH_, vAxis);
    View.normalize();

    // rotate the view vector by the vertical angle around the horizontal axis
    Vector3f hAxis = vAxis.crossProduct(View);
    hAxis.normalize();
    View.rotate(angleV_, hAxis);
    View.normalize();
       
    target_ = View;
    target_.normalize();

    up_ = target_.crossProduct(hAxis);
    up_.normalize();

    //Logger::write(Logger::ss << "position:" << position_ << ", target:" << target_ << ", up:" << up_);

    updateView();
}

void Camera::updateView()
{
    Matrix4f cameraTranslate;
    Matrix4f cameraRotate;

    cameraTranslate.initTranslationTransform(-position_.x(), -position_.y(), -position_.z());
    cameraRotate = Math::genCameraTransform(target_, up_);
    view_ = cameraRotate * cameraTranslate;
}

void Camera::updateProjection()
{
    projection_ = Math::genPersProjTransform(fov_, width_, height_, zNear_, zFar_);
}

Matrix4f Camera::view()
{
    if(viewDirty_) {
        updateView();
    }
    return view_;
}

Matrix4f Camera::projection()
{
    if (projectionDirty_) {
        updateProjection();
    }
    return projection_;
}

void Camera::move(CameraDirection dir, float distance)
{
    switch(dir) {
        case CAMERA_DIRECTION_FORWARD:
        {
            position_ = position_ - (target_ * distance);

            break;
        }

        case CAMERA_DIRECTION_BACKWARD:
        {
            position_ = position_ + (target_ * distance);
            break;
        }

        case CAMERA_DIRECTION_LEFT:
        {
            Vector3f left = target_.crossProduct(up_);
            left.normalize();
            left = left * distance;
            position_ = position_ + left;

            break;
        }

        case CAMERA_DIRECTION_RIGHT:
        {
            Vector3f right = up_.crossProduct(target_);
            right.normalize();
            right = right * distance;
            position_ = position_ + right;

            break;
        }

        case CAMERA_DIRECTION_UP:
        {
            position_ = position_ + (up_ * distance);
            break;
        }

        case CAMERA_DIRECTION_DOWN:
        {
            position_ = position_ - (up_ * distance);
            break;
        }
    }
    viewDirty_ = true;
    //Logger::write(Logger::ss << "Camera position: " << position_);
}

void Camera::rotate(CameraAxis axis, float angle)
{
    switch (axis) {
        case CAMERA_AXIS_X:
            angleV_ -= angle;
            if(angleV_ > kMaxVAngle) angleV_ = kMaxVAngle;
            else if(angleV_ < kMinVAngle) angleV_ = kMinVAngle;
            break;

        case CAMERA_AXIS_Y:
            angleH_ -= angle;
            break;
    }

    update();
}


void Camera::setWidth(float width)
{
    width_ = width;
    projectionDirty_ = true;
}

void Camera::setHeight(float height)
{
    height_ = height;
    projectionDirty_ = true;
}

void Camera::setFovRel(float fov)
{
    fov_ += fov;
    projectionDirty_ = true;
}

void Camera::setZNear(float zNear)
{
    zNear_ = zNear;
    projectionDirty_ = true;
}
void Camera::setZFar(float zFar)
{
    zFar_ = zFar;
    projectionDirty_ = true;
}

void Camera::setZNearRel(float zNear)
{
    zNear_ += zNear;
    projectionDirty_ = true;
}

void Camera::setZFarRel(float zFar)
{
    zFar_ += zFar;
    projectionDirty_ = true;

}
