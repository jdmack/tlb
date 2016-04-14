#ifndef TLB_EVENT_EVENT_DISPATCHER_H_
#define TLB_EVENT_EVENT_DISPATCHER_H_

#include "event/Event.h"
#include <vector>
#include <list>

class EventHandler;

class EventDispatcher
{

    private:
        //std::vector<EventHandler *> handlers_;
        std::list<EventHandler *> handlers_;

        static EventDispatcher * instance_;

    public:
        EventDispatcher();
        ~EventDispatcher();
        
        static EventDispatcher * instance();

        void registerHandler(EventHandler * handler);
        void sendEvent(Event * event);

};

#endif
