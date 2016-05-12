#include <iostream>
#include <cmath>
#include "gfx/Camera.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "math/Math.h"

const static float kStepScale = 1.0f;
const static float kAngleStep = 10.0f;
const static float kEdgeStep = 0.5f;
const static int kMargin = 100;

Camera::Camera(int windowWidth, int windowHeight)
{
    windowWidth_  = windowWidth;
    windowHeight_ = windowHeight;

    //position_ = Vector3f(0.0f, 0.0f, 0.0f);
    position_ = Vector3f(0.0f, 0.0f, 1.0f);
    target_   = Vector3f(0.0f, 0.0f, 1.0f);
    up_       = Vector3f(0.0f, 1.0f, 0.0f);

    target_.normalize();

    updateView();

    persProjInfo_.fov_ = 60.0f;
    persProjInfo_.width_ = windowWidth;
    persProjInfo_.height_ = windowHeight;
    persProjInfo_.zNear_ = 1.0f;
    persProjInfo_.zFar_ = 2000.0f;


    init();
}


Camera::Camera(int windowWidth, int windowHeight, const Vector3f & position, const Vector3f & target, const Vector3f& up)
{
    windowWidth_  = windowWidth;
    windowHeight_ = windowHeight;
    position_ = position;

    target_ = target;
    target_.normalize();

    up_ = up;
    up_.normalize();

    updateView();

    persProjInfo_.fov_ = 60.0f;
    persProjInfo_.width_ = windowWidth;
    persProjInfo_.height_ = windowHeight;
    persProjInfo_.zNear_ = 1.0f;
    persProjInfo_.zFar_ = 100.0f;

    init();
}


void Camera::init()
{
    Vector3f hTarget(target_.x(), 0.0, target_.z());
    hTarget.normalize();
    
    if (hTarget.z() >= 0.0f)
    {
        if (hTarget.x() >= 0.0f)
        {
            angleH_ = 360.0f - toDegree(asin(hTarget.z()));
        }
        else
        {
            angleH_ = 180.0f + toDegree(asin(hTarget.z()));
        }
    }
    else
    {
        if (hTarget.x() >= 0.0f)
        {
            angleH_ = toDegree(asin(-hTarget.z()));
        }
        else
        {
            angleH_ = 90.0f + toDegree(asin(-hTarget.z()));
        }
    }
    
    angleV_ = -toDegree(asin(target_.y()));

    onUpperEdge_ = false;
    onLowerEdge_ = false;
    onLeftEdge_  = false;
    onRightEdge_ = false;
    mousePosition_.setX(windowWidth_ / 2);
    mousePosition_.setY(windowHeight_ / 2);

    Game::instance()->renderer()->warpMouse(mousePosition_);
}


bool Camera::onKeyboard(KeyType key)
{
    bool ret = false;

    switch(key) {
        case KEY_W:
        case KEY_UP:
            move(CAMERA_DIRECTION_FORWARD, kStepScale);
            break;

        case KEY_S:
        case KEY_DOWN:
        {
            move(CAMERA_DIRECTION_BACKWARD, kStepScale);
            break;
        }

        case KEY_A:
        case KEY_LEFT:
        {
            move(CAMERA_DIRECTION_LEFT, kStepScale);

            break;
        }

        case KEY_D:
        case KEY_RIGHT:
        {
            move(CAMERA_DIRECTION_RIGHT, kStepScale);

            break;
        }

        case KEY_SPACE:
        {
            move(CAMERA_DIRECTION_UP, kStepScale);
            break;
        }

        case KEY_C:
        {
            move(CAMERA_DIRECTION_DOWN, kStepScale);
            break;
        }
        
        case KEY_PAGE_UP:
            position_.setY(position_.y() + kStepScale);
            break;
    
        case KEY_PAGE_DOWN:
            position_.setY(position_.y() - kStepScale);
            break;
    
        default:
            break;            
    }

    return ret;
}


void Camera::onMouse(int x, int y)
{
    const int deltaX = x - mousePosition_.x();
    const int deltaY = y - mousePosition_.y();

    mousePosition_.setX(x);
    mousePosition_.setY(y);

    angleH_ += (float)deltaX / kAngleStep;
    angleV_ += (float)deltaY / kAngleStep;

    if (deltaX == 0) {
        if (x <= kMargin) {
            onLeftEdge_ = true;
        }
        else if (x >= (windowWidth_ - kMargin)) {
            onRightEdge_ = true;
        }
    }
    else {
        onLeftEdge_ = false;
        onRightEdge_ = false;
    }

    if (deltaY == 0) {
        if (y <= kMargin) {
            onUpperEdge_ = true;
        }
        else if (y >= (windowHeight_ - kMargin)) {
            onLowerEdge_ = true;
        }
    }
    else {
        onUpperEdge_ = false;
        onLowerEdge_ = false;
    }

    update();
}


void Camera::onRender()
{
    bool doUpdate = false;

    if (onLeftEdge_) {
        angleH_ -= kEdgeStep;
        doUpdate = true;
    }
    else if (onRightEdge_) {
        angleH_ += kEdgeStep;
        doUpdate = true;
    }

    if (onUpperEdge_) {
        if (angleV_ > -90.0f) {
            angleV_ -= kEdgeStep;
            doUpdate = true;
        }
    }
    else if (onLowerEdge_) {
        if (angleV_ < 90.0f) {
           angleV_ += kEdgeStep;
           doUpdate = true;
        }
    }

    if (doUpdate) {
        update();
    }
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

