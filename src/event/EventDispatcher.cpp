#include "event/EventDispatcher.h"
#include "event/EventHandler.h"
#include <vector>


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


void EventDispatcher::registerHandler(EventHandler * handler)
{
    handlers_.push_front(handler);
}

void EventDispatcher::sendEvent(Event * event)
{
    for(std::list<EventHandler *>::iterator iterator = handlers_.begin(); iterator != handlers_.end(); ++iterator) {
        if((*iterator)->handleEvent(event)) {
            break;
        }
    }
}

void EventDispatcher::removeHandler(int id)
{
    for(std::list<EventHandler *>::iterator iterator = handlers_.begin(); iterator != handlers_.end(); ++iterator) {
        if((*iterator)->id() == id) {
            handlers_.erase(iterator);
            break;
        }
    }
}




