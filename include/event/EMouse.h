#ifndef TLB_EVENT_E_MOUSE_H_
#define TLB_EVENT_E_MOUSE_H_

#include "event/Event.h"
#include "math/Vector2i.h"

enum MouseButton {
    MOUSE_BUTTON_NONE,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT
};

class EMouse: public Event
{
    private:
        MouseButton button_;
        Vector2i position_;

    public:
        EMouse();
        EMouse(MouseButton keyType, Vector2i position);
        EMouse(EventType type);
        ~EMouse();

        // accessors
        MouseButton button() const { return button_; }
        Vector2i position() const { return position_; }

        // mutators
        void setButton(MouseButton button) { button_ = button; }
        void setPosition(Vector2i position) { position_ = position; }

};

#endif

