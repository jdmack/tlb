#include <iostream>
#include <cmath>
#include "gfx/Camera.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "math/Math.h"
#include "util/Logger.h"

Camera::Camera(int windowWidth, int windowHeight)
{
    //position_ = Vector3f(0.0f, 0.0f, 1.0f);
    //target_   = Vector3f(0.0f, 0.0f, 1.0f);
    //up_       = Vector3f(0.0f, 1.0f, 0.0f);
    position_ = Vector3f(11.0f, 12.0f, -0.5f);
    target_   = Vector3f(0.0f, -1.0f, 0.5f);
    up_       = Vector3f(0.0f, 0.5f, 1.0f);

    target_.normalize();

    updateView();

    persProjInfo_.fov_ = 60.0f;
    persProjInfo_.width_ = windowWidth;
    persProjInfo_.height_ = windowHeight;
    persProjInfo_.zNear_ = 0.1f;
    persProjInfo_.zFar_ = 100.0f;

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

    persProjInfo_.fov_ = 60.0f;
    persProjInfo_.width_ = windowWidth;
    persProjInfo_.height_ = windowHeight;
    persProjInfo_.zNear_ = 0.1f;
    persProjInfo_.zFar_ = 100.0f;

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
    //std::cout << "position:" << position_ << ", target:" << target_ << ", up:" << up_ << std::endl;
    updateView();
}

void Camera::updateView()
{
    Matrix4f cameraTranslate;
    Matrix4f cameraRotate;

    cameraTranslate.initTranslationTransform(-position_.x(), -position_.y(), -position_.z());
    cameraRotate.initCameraTransform(target_, up_);
    view_ = cameraRotate * cameraTranslate;
}

Matrix4f Camera::view()
{
    updateView();
    return view_;
}

Matrix4f Camera::projection()
{
    projection_.initPersProjTransform(persProjInfo_);
    return projection_;
}


void Camera::move(CameraDirection dir, float distance)
{
    switch(dir) {
        case CAMERA_DIRECTION_FORWARD:
        {
            position_ = position_ + (target_ * distance);

            break;
        }

        case CAMERA_DIRECTION_BACKWARD:
        {
            position_ = position_ - (target_ * distance);
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
    updateView();
}

void Camera::rotate(CameraAxis axis, float angle)
{
    switch (axis) {
        case CAMERA_AXIS_X:
            angleV_ += angle;
            break;

        case CAMERA_AXIS_Y:
            angleH_ += angle;
            break;
    }

    update();
}

