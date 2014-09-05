#include "event/event_dispatcher.h"
#include "event/event_handle.h"

EventDispatcher * instance_;

EventDispatcher * EventDispatcher::instance()
{
    if(instance_ == nullptr) {
        instance_ = new EventDispatcher();
    }
    return instance_;
}


void EventDispatcher::register_handler(EventHandler * handler)
{
    // Add to handler_list_
}

void EventDispatcher::send_event(Event event)
{

}
