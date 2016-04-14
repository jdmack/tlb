#ifndef TLB_EVENT_EVENT_HANDLER_H_
#define TLB_EVENT_EVENT_HANDLER_H_

#include "event/Event.h"

class EventHandler
{
    public:
        EventHandler();
        ~EventHandler();
        virtual void handleEvent(Event * event);

};

#endif
