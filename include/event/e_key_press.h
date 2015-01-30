#ifndef TLB_EVENT_E_KEY_PRESS_H_
#define TLB_EVENT_E_KEY_PRESS_H_

#include "event/event.h"

class EKeyPress : public Event
{
    private:
        KeyType key_type_;

    public:
        EKeyPress();
        EKeyPress(KeyType key_type);
        ~EKeyPress();

        // accessors
        KeyType key_type() const { return key_type_; }

};

#endif

