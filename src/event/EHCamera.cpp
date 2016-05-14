#include <list>
#include "event/EHCamera.h"
#include "event/Event.h"
#include "event/EKeyPress.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Camera.h"

#include <iostream>

const static float kStepScale = 1.0f;
const static float kAngleStep = 10.0f;
const static float kEdgeStep = 0.5f;
const static int kMargin = 100;

EHCamera::EHCamera() : EventHandler()
{
    toggleKey_ = KEY_NONE;
    mousePosition_ = Vector2i(0, 0);

    onUpperEdge_ = false;
    onLowerEdge_ = false;
    onLeftEdge_  = false;
    onRightEdge_ = false;

}

EHCamera::~EHCamera()
{

}

bool EHCamera::handleEvent(Event * event)
{
    bool ret = false;
    switch(event->type()) {
        case EVENT_MOUSE_CLICK:    
        {
            break;
        }

        case EVENT_MOUSE_MOTION:
        {

            break;
        }
        
        case EVENT_KEY_PRESS:
        {
            EKeyPress * keyPressEvent = static_cast<EKeyPress *>(event);
            ret = keyPress(keyPressEvent->keyType());
            break;
        }

    }

    return ret;
}

bool EHCamera::mouseLeftClick(Vector2i position)
{
    return false;
}

bool EHCamera::mouseRightClick(Vector2i position)
{
    return false;
}

bool EHCamera::mouseMotion(Vector2i position)
{
    const int deltaX = position.x() - mousePosition_.x();
    const int deltaY = position.y() - mousePosition_.y();

    int windowWidth = Game::instance()->renderer()->screenWidth();
    int windowHeight = Game::instance()->renderer()->screenHeight();

    mousePosition_ = position;

    float angleH = (float)deltaX / kAngleStep;
    float angleV = (float)deltaY / kAngleStep;

    if(deltaX == 0) {
        if(position.x() <= kMargin) {
            onLeftEdge_ = true;
        }
        else if(position.x() >= (windowWidth - kMargin)) {
            onRightEdge_ = true;
        }
    }
    else {
        onLeftEdge_ = false;
        onRightEdge_ = false;
    }

    if(deltaY == 0) {
        if(position.y() <= kMargin) {
            onUpperEdge_ = true;
        }
        else if(position.y() >= (windowHeight - kMargin)) {
            onLowerEdge_ = true;
        }
    }
    else {
        onUpperEdge_ = false;
        onLowerEdge_ = false;
    }
 
    Game::instance()->renderer()->camera()->rotate(CAMERA_AXIS_X, angleH);
    Game::instance()->renderer()->camera()->rotate(CAMERA_AXIS_Z, angleV);

    return false;
}

bool EHCamera::keyPress(KeyType key)
{
    std::cout << "Hi" << std::endl;
    bool ret = false;
    switch(key) {
        case KEY_W:
        case KEY_UP:
            Game::instance()->renderer()->camera()->move(CAMERA_DIRECTION_FORWARD, kStepScale);
            break;

        case KEY_S:
        case KEY_DOWN:
        {   
            Game::instance()->renderer()->camera()->move(CAMERA_DIRECTION_BACKWARD, kStepScale);
            break;
        }

        case KEY_A:
        case KEY_LEFT:
        {   
            Game::instance()->renderer()->camera()->move(CAMERA_DIRECTION_LEFT, kStepScale);

            break;
        }

        case KEY_D:
        case KEY_RIGHT:
        {   
            Game::instance()->renderer()->camera()->move(CAMERA_DIRECTION_RIGHT, kStepScale);

            break;
        }

        case KEY_SPACE:
        {   
            Game::instance()->renderer()->camera()->move(CAMERA_DIRECTION_UP, kStepScale);
            break;
        }
        case KEY_C:
        {
            Game::instance()->renderer()->camera()->move(CAMERA_DIRECTION_DOWN, kStepScale);
            break;
        }

        case KEY_PAGE_UP:
            //position_.setY(position_.y() + kStepScale);
            break;

        case KEY_PAGE_DOWN:
            //position_.setY(position_.y() - kStepScale);
            break;

        default:
            break;
    }

    return ret;
}

