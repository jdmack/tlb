#include "event/EMouseClick.h"
#include "event/Event.h"
#include "Point.h"

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
