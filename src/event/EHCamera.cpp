#include <list>
#include "event/EHCamera.h"
#include "event/Event.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Camera.h"


const static float kStepScale = 1.0f;

EHCamera::EHCamera()
{
    toggleKey_ = KEY_NONE;
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

bool EHCamera::keyPress(KeyType key)
{
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
