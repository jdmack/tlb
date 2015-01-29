#ifndef TLB_EVENT_EH_LEVEL_H_
#define TLB_EVENT_EH_LEVEL_H_

#include "event/event.h"
#include "event/event_handler.h"
class EHLevel : public EventHandler
{
    public:
        EHLevel();
        ~EHLevel();

        void handle_event(Event event);

};

#endif
