#ifndef TLB_EVENT_EVENT_DISPATCHER_H_
#define TLB_EVENT_EVENT_DISPATCHER_H_

#include "event/event.h"
#include <vector>

class EventHandler;

class EventDispatcher
{

    private:
        std::vector<EventHandler *> handlers_;

        static EventDispatcher * instance_;

    public:
        EventDispatcher();
        ~EventDispatcher();
        
        static EventDispatcher * instance();

        void register_handler(EventHandler * handler);
        void send_event(Event event);

};

#endif
