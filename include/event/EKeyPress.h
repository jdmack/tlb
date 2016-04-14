#ifndef TLB_EVENT_E_KEY_PRESS_H_
#define TLB_EVENT_E_KEY_PRESS_H_

#include "event/Event.h"

class EKeyPress : public Event
{
    private:
        KeyType keyType_;

    public:
        EKeyPress();
        EKeyPress(KeyType keyType);
        ~EKeyPress();

        // accessors
        KeyType keyType() const { return keyType_; }

};

#endif

