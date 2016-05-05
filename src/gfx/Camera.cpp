#include "gfx/Camera.h"
#include "util/math/Math.h"

const static float STEP_SCALE = 1.0f;
const static float EDGE_STEP = 0.5f;
const static int MARGIN = 10;

Camera::Camera(int WindowWidth, int WindowHeight)
{
    m_windowWidth  = WindowWidth;
    m_windowHeight = WindowHeight;
    position_          = Vector3(0.0f, 0.0f, 0.0f);
    target_       = Vector3(0.0f, 0.0f, 1.0f);
    target_.normalize();
    up_           = Vector3(0.0f, 1.0f, 0.0f);

    init();
}


Camera::Camera(int WindowWidth, int WindowHeight, const Vector3& Pos, const Vector3& Target, const Vector3& Up)
{
    m_windowWidth  = WindowWidth;
    m_windowHeight = WindowHeight;
    position_ = Pos;

    target_ = Target;
    target_.normalize();

    up_ = Up;
    up_.normalize();

    init();
}


void Camera::init()
{
    Vector3 HTarget(target_.x, 0.0, target_.z);
    HTarget.normalize();
    
    if (HTarget.z >= 0.0f)
    {
        if (HTarget.x >= 0.0f)
        {
            angleH_ = 360.0f - toDegree(asin(HTarget.z));
        }
        else
        {
            angleH_ = 180.0f + toDegree(asin(HTarget.z));
        }
    }
    else
    {
        if (HTarget.x >= 0.0f)
        {
            angleH_ = toDegree(asin(-HTarget.z));
        }
        else
        {
            angleH_ = 90.0f + toDegree(asin(-HTarget.z));
        }
    }
    
    angleV_ = -toDegree(asin(target_.y));

    onUpperEdge_ = false;
    onLowerEdge_ = false;
    onLeftEdge_  = false;
    onRightEdge_ = false;
    mousePosition_.x  = m_windowWidth / 2;
    mousePosition_.y  = m_windowHeight / 2;

   // glutWarpPointer(mousePosition_.x, mousePosition_.y);
}


bool Camera::onKeyboard(KeyType Key)
{
    bool Ret = false;

    switch (Key) {

    case KEY_UP:
        {
            position_ += (target_ * STEP_SCALE);
            Ret = true;
        }
        break;

    case KEY_DOWN:
        {
            position_ -= (target_ * STEP_SCALE);
            Ret = true;
        }
        break;

    case KEY_LEFT:
        {
            Vector3 Left = target_.crossProduct(up_);
            Left.normalize();
            Left *= STEP_SCALE;
            position_ += Left;
            Ret = true;
        }
        break;

    case KEY_RIGHT:
        {
            Vector3 Right = up_.crossProduct(target_);
            Right.normalize();
            Right *= STEP_SCALE;
            position_ += Right;
            Ret = true;
        }
        break;
        
    case KEY_PAGE_UP:
        position_.y += STEP_SCALE;
        break;
    
    case KEY_PAGE_DOWN:
        position_.y -= STEP_SCALE;
        break;
    
    default:
        break;            
    }

    return Ret;
}


void Camera::onMouse(int x, int y)
{
    const int DeltaX = x - mousePosition_.x;
    const int DeltaY = y - mousePosition_.y;

    mousePosition_.x = x;
    mousePosition_.y = y;

    angleH_ += (float)DeltaX / 20.0f;
    angleV_ += (float)DeltaY / 20.0f;

    if (DeltaX == 0) {
        if (x <= MARGIN) {
        //    angleH_ -= 1.0f;
            onLeftEdge_ = true;
        }
        else if (x >= (m_windowWidth - MARGIN)) {
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
        else if (y >= (m_windowHeight - MARGIN)) {
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
    const Vector3 Vaxis(0.0f, 1.0f, 0.0f);

    // rotate the view vector by the horizontal angle around the vertical axis
    Vector3 View(1.0f, 0.0f, 0.0f);
    View.rotate(angleH_, Vaxis);
    View.normalize();

    // rotate the view vector by the vertical angle around the horizontal axis
    Vector3 Haxis = Vaxis.crossProduct(View);
    Haxis.normalize();
    View.rotate(angleV_, Haxis);
       
    target_ = View;
    target_.normalize();

    up_ = target_.Cross(Haxis);
    up_.normalize();
}
