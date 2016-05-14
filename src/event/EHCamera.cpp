#include <list>
#include "event/EHCamera.h"
#include "event/Event.h"
#include "event/EKeyPress.h"
#include "event/EMouse.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Camera.h"

#include <iostream>

const static float kStepScale = 1.0f;
const static float kAngleStep = 10.0f;

EHCamera::EHCamera() : EventHandler()
{
    toggleKey_ = KEY_NONE;
    mousePosition_ = Vector2i(
        Game::instance()->renderer()->screenWidth() / 2, 
        Game::instance()->renderer()->screenHeight() / 2);
}

EHCamera::~EHCamera()
{

}

bool EHCamera::handleEvent(Event * event)
{
    bool ret = true;
    switch(event->type()) {
        case EVENT_MOUSE_CLICK:    
        {

            break;
        }

        case EVENT_MOUSE_MOTION:
        {
            EMouse * mouseEvent = static_cast<EMouse *>(event);
            ret = mouseMotion(Vector2i(mouseEvent->position()));

            break;
        }
        
        case EVENT_KEY_PRESS:
        {
            EKeyPress * keyPressEvent = static_cast<EKeyPress *>(event);
            ret = keyPress(keyPressEvent->keyType());
            break;
        }
        case EVENT_WINDOW_FOCUS_GAINED:
        {
            break;
        }
        case EVENT_WINDOW_FOCUS_LOST:
        {
            break;
        }
        default:
            ret = false;
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
    // only if we have window focus
    if(!Game::instance()->renderer()->windowFocused()) {
        return true;
    }

    const int deltaX = position.x() - mousePosition_.x();
    const int deltaY = position.y() - mousePosition_.y();

    float angleH = (float)deltaX / kAngleStep;
    float angleV = (float)deltaY / kAngleStep;
 
    Game::instance()->renderer()->camera()->rotate(CAMERA_AXIS_Y, angleH);
    Game::instance()->renderer()->camera()->rotate(CAMERA_AXIS_X, angleV);
    Game::instance()->renderer()->warpMouse(mousePosition_);

    return true;
}

bool EHCamera::keyPress(KeyType key)
{
    bool ret = true;
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

        default:
            ret = false;
            break;
    }

    return ret;
}

