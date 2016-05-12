#include "event/EMouse.h"
#include "event/Event.h"

EMouse::EMouse()
{
    type_ = EVENT_MOUSE_CLICK;
    button_ = MOUSE_BUTTON_NONE;
    position_ = Vector2i(0, 0);
}

EMouse::EMouse(MouseButton button, Vector2i position)
{
    type_ = EVENT_MOUSE_CLICK;
    button_ = button;
    position_ = position;
}

EMouse::EMouse(EventType type) : Event(type)
{
    button_ = MOUSE_BUTTON_NONE;
    position_ = Vector2i(0, 0);
}

EMouse::~EMouse()
{

}
