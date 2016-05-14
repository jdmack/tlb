#ifndef TLB_EVENT_EVENT_HANDLER_H_
#define TLB_EVENT_EVENT_HANDLER_H_

#include "event/Event.h"

class EventHandler
{
    private: 
        int id_;
        static int idCounter_;

    public:
        EventHandler();
        ~EventHandler();
        virtual bool handleEvent(Event * event);

        // accessors
        int id() const { return id_; }

};

#endif
