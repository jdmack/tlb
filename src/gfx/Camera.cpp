#include <iostream>
#include <cmath>
#include "gfx/Camera.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "math/Math.h"

const static float STEP_SCALE = 1.0f;
const static float EDGE_STEP = 0.5f;
const static int MARGIN = 30;

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
    persProjInfo_.zFar_ = 100.0f;


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


bool Camera::onKeyboard(KeyType key)
{
    bool Ret = false;

    switch(key) {
        case KEY_W:
        case KEY_UP:
        {
            position_ = position_ + (target_ * STEP_SCALE);
            Ret = true;

            break;
        }

        case KEY_S:
        case KEY_DOWN:
        {
            position_ = position_ - (target_ * STEP_SCALE);
            Ret = true;
            break;
        }

        case KEY_A:
        case KEY_LEFT:
        {
            Vector3f Left = target_.crossProduct(up_);
            Left.normalize();
            Left = Left *STEP_SCALE;
            position_ = position_ + Left;
            Ret = true;

            break;
        }

        case KEY_D:
        case KEY_RIGHT:
        {
            Vector3f Right = up_.crossProduct(target_);
            Right.normalize();
            Right = Right * STEP_SCALE;
            position_ = position_ + Right;
            Ret = true;

            break;
        }

        case KEY_SPACE:
        {
            position_ = position_ + (up_ * STEP_SCALE);
            Ret = true;
            break;
        }

        case KEY_C:
        {
            position_ = position_ - (up_ * STEP_SCALE);
            Ret = true;
            break;
        }
        
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
    const int deltaX = x - mousePosition_.x();
    const int deltaY = y - mousePosition_.y();

    mousePosition_.setX(x);
    mousePosition_.setY(y);

    std::cout << "mouse( " << x << "," << y << ")" << std::endl;
    std::cout << "delta( " << deltaX << "," << deltaY << ")" << std::endl;

    angleH_ += (float)deltaX / 20.0f;
    angleV_ += (float)deltaY / 20.0f;

    if (deltaX == 0) {
        if (x <= MARGIN) {
            onLeftEdge_ = true;
        }
        else if (x >= (windowWidth_ - MARGIN)) {
            onRightEdge_ = true;
        }
    }
    else {
        onLeftEdge_ = false;
        onRightEdge_ = false;
    }

    if (deltaY == 0) {
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
    View.normalize();
       
    target_ = View;
    target_.normalize();

    up_ = target_.crossProduct(Haxis);
    up_.normalize();
    updateView();
}

void Camera::updateView()
{
    Matrix4f cameraTranslate;
    Matrix4f cameraRotate;

    cameraTranslate.initTranslationTransform(-position_.x(), -position_.y(), -position_.z());
    cameraRotate.initCameraTransform(target_, up_);
    //std::cout << "angleH: " << angleH_ << ", angleV: " << angleV_ << std::endl;
    //std::cout << "target: " << std::endl;
    //target_.print();
    //std::cout << "up: " << std::endl;
    //up_.print();


    /*
    std::cout << "cameraTranslate: " << std::endl;
    cameraRotate.print();
    std::cout << "cameraRotate: " << std::endl;
    cameraTranslate.print();
    */


    view_ = cameraRotate * cameraTranslate;
    //std::cout << "View: " << std::endl;
    //view_.print();
}

Matrix4f Camera::view()
{
    updateView();
    return view_;
}

