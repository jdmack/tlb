#include "event/e_mouse_click.h"
#include "event/event.h"
#include "point.h"

EMouseClick::EMouseClick()
{
    type_ = EVENT_MOUSE_CLICK;
    button_ = MOUSE_LEFT;
    point_ = Point(0, 0);
}

EMouseClick::EMouseClick(MouseButton button, Point point)
{
    type_ = EVENT_MOUSE_CLICK;
    button_ = button;
    point_ = point;
}

EMouseClick::~EMouseClick()
{

}
