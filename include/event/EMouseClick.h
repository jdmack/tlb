#ifndef TLB_EVENT_E_MOUSE_CLICK_H_
#define TLB_EVENT_E_MOUSE_CLICK_H_

#include "event/Event.h"
#include "Point.h"

enum MouseButton {
    MOUSE_LEFT,
    MOUSE_RIGHT
};

class EMouseClick : public Event
{
    private:
        MouseButton button_;
        Point point_;

    public:
        EMouseClick();
        EMouseClick(MouseButton keyType, Point point);
        ~EMouseClick();

        // accessors
        MouseButton button() const { return button_; }
        Point point() const { return point_; }

};

#endif

