#include <list>
#include "event/EHCamera.h"
#include "event/Event.h"


EHCamera::EHCamera()
{
    toggleKey_ = KEY_NONE;
}

EHCamera::~EHCamera()
{

}

void EHCamera::handleEvent(Event * event)
{
    switch(event->type()) {
        case EVENT_MOUSE_CLICK:    
        {
            break;
        }

        case EVENT_MOUSE_MOTION:

            break;
        
        case EVENT_KEY_PRESS:

            break;

    }

}

void EHCamera::mouseLeftClick(Point point)
{

}

void EHCamera::mouseRightClick(Point point)
{
}

void EHCamera::keyPress(KeyType key)
{
    switch(key) {

        case KEY_ESCAPE:
            break;

        case KEY_SPACE:
            break;

        case KEY_S:
            break;
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_A:
            break;
        case KEY_B:
            break;
        case KEY_C:
        case KEY_D:
        case KEY_E:
        case KEY_F:
        case KEY_G:
        case KEY_H:
        case KEY_I:
        case KEY_J:
        case KEY_K:
        case KEY_L:
        case KEY_M:
        case KEY_N:
        case KEY_O:
        case KEY_P:
        case KEY_Q:
        case KEY_R:
        case KEY_T:
        case KEY_U:
        case KEY_V:
        case KEY_W:
        case KEY_X:
        case KEY_Y:
        case KEY_Z:
        case KEY_NONE:
            break;
    }
}
