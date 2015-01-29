#include "event/event_dispatcher.h"
#include "event/event_handle.h"


EventDispatcher * EventDispatcher::instance_ = nullptr;

EventDispatcher::EventDispatcher()
{

}

EventDispatcher::~EventDispatcher()
{

}

EventDispatcher * EventDispatcher::instance()
{
    if(instance_ == nullptr) {
        instance_ = new EventDispatcher();
    }
    return instance_;
}


void EventDispatcher::register_handler(EventHandler * handler)
{
    handlers_.push_back(handler);
}

void EventDispatcher::send_event(Event event)
{
    for(std::vector<EventHandler *>::iterator iterator = handlers_.begin(); iterator != handlers_.end(); ++iterator) {
        (*iterator)->handle_event(event);
    }
}

