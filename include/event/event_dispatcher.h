#ifndef TLB_EVENT_EVENT_DISPATCHER_H_
#define TLB_EVENT_EVENT_DISPATCHER_H_

#include "event/event.h"

class EventHandler;

class EventDispatcher
{

    private:
        EventDispatcher();

        static EventDispatcher * instance_;

        std::list<EventHandler *> device_list_;

    public:
        EventDispatcher(const EventDispatcher &) = delete;
        EventDispatcher& operator=(const EventDispatcher &) = delete;
        ~EventDispatcher();
        
        static EventDispatcher * instance();

        void register_handler(EventHandler * device);

        void send_event(Event event);

};

#endif
