#ifndef TLB_EVENT_EVENT_H_
#define TLB_EVENT_EVENT_H_

enum EventType {
    EVENT_MOUSE_CLICK,
    EVENT_KEY_PRESS,
    EVENT_GAME_QUIT,
    EVENT_BLANK
};

enum KeyType {
    KEY_ESCAPE,
    KEY_SPACE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_NONE
};

class Event
{
    protected:
        EventType type_;
    public:
        Event();
        ~Event();

        // accessors
        EventType type() const { return type_; }

};

#endif

