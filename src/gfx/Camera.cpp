#include <cmath>
#include "gfx/Camera.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "math/Math.h"

const static float STEP_SCALE = 1.0f;
const static float EDGE_STEP = 0.5f;
const static int MARGIN = 10;

Camera::Camera(int windowWidth, int windowHeight)
{
    windowWidth_  = windowWidth;
    windowHeight_ = windowHeight;

    position_ = Vector3f(0.0f, 0.0f, 0.0f);
    target_   = Vector3f(0.0f, 0.0f, 1.0f);
    up_       = Vector3f(0.0f, 1.0f, 0.0f);

    target_.normalize();

    updateView();

    //init();
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

    //init();
}


void Camera::init()
{
    Vector3f HTarget(target_.x(), 0.0, target_.z());
    HTarget.normalize();
    
    if (HTarget.z() >= 0.0f)
    {
        if (HTarget.x() >= 0.0f)
        {
            angleH_ = 360.0f - toDegree(asin(HTarget.z()));
        }
        else
        {
            angleH_ = 180.0f + toDegree(asin(HTarget.z()));
        }
    }
    else
    {
        if (HTarget.x() >= 0.0f)
        {
            angleH_ = toDegree(asin(-HTarget.z()));
        }
        else
        {
            angleH_ = 90.0f + toDegree(asin(-HTarget.z()));
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


bool Camera::onKeyboard(KeyType Key)
{
    bool Ret = false;

    switch (Key) {

    case KEY_UP:
        {
            position_ = position_ + (target_ * STEP_SCALE);
            Ret = true;
        }
        break;

    case KEY_DOWN:
        {
            position_ = position_ - (target_ * STEP_SCALE);
            Ret = true;
        }
        break;

    case KEY_LEFT:
        {
            Vector3f Left = target_.crossProduct(up_);
            Left.normalize();
            Left = Left *STEP_SCALE;
            position_ = position_ + Left;
            Ret = true;
        }
        break;

    case KEY_RIGHT:
        {
            Vector3f Right = up_.crossProduct(target_);
            Right.normalize();
            Right = Right * STEP_SCALE;
            position_ = position_ + Right;
            Ret = true;
        }
        break;
        
    case KEY_PAGE_UP:
        position_.setY(position_.y() + STEP_SCALE);
        break;
    
    case KEY_PAGE_DOWN:
        position_.setY(position_.y() - STEP_SCALE);
        break;
    
    default:
        break;            
    }

    return Ret;
}


void Camera::onMouse(int x, int y)
{
    const int DeltaX = x - mousePosition_.x();
    const int DeltaY = y - mousePosition_.y();

    mousePosition_.setX(x);
    mousePosition_.setY(y);

    angleH_ += (float)DeltaX / 20.0f;
    angleV_ += (float)DeltaY / 20.0f;

    if (DeltaX == 0) {
        if (x <= MARGIN) {
        //    angleH_ -= 1.0f;
            onLeftEdge_ = true;
        }
        else if (x >= (windowWidth_ - MARGIN)) {
        //    angleH_ += 1.0f;
            onRightEdge_ = true;
        }
    }
    else {
        onLeftEdge_ = false;
        onRightEdge_ = false;
    }

    if (DeltaY == 0) {
        if (y <= MARGIN) {
            onUpperEdge_ = true;
        }
        else if (y >= (windowHeight_ - MARGIN)) {
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
    bool ShouldUpdate = false;

    if (onLeftEdge_) {
        angleH_ -= EDGE_STEP;
        ShouldUpdate = true;
    }
    else if (onRightEdge_) {
        angleH_ += EDGE_STEP;
        ShouldUpdate = true;
    }

    if (onUpperEdge_) {
        if (angleV_ > -90.0f) {
            angleV_ -= EDGE_STEP;
            ShouldUpdate = true;
        }
    }
    else if (onLowerEdge_) {
        if (angleV_ < 90.0f) {
           angleV_ += EDGE_STEP;
           ShouldUpdate = true;
        }
    }

    if (ShouldUpdate) {
        update();
    }
}

void Camera::update()
{
    const Vector3f Vaxis(0.0f, 1.0f, 0.0f);

    // rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);
    View.rotate(angleH_, Vaxis);
    View.normalize();

    // rotate the view vector by the vertical angle around the horizontal axis
    Vector3f Haxis = Vaxis.crossProduct(View);
    Haxis.normalize();
    View.rotate(angleV_, Haxis);
       
    target_ = View;
    target_.normalize();

    up_ = target_.crossProduct(Haxis);
    up_.normalize();
}

void Camera::updateView()
{
    Matrix4f cameraTranslate;
    Matrix4f cameraRotate;

    cameraTranslate.initTranslationTransform(-position_.x(), -position_.y(), -position_.z());
    cameraRotate.initCameraTransform(target_, up_);

    view_ = cameraRotate * cameraTranslate;
}

