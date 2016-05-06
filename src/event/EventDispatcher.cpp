#include "event/EventDispatcher.h"
#include "event/EventHandler.h"
#include <vector>


EventDispatcher * EventDispatcher::instance_ = nullptr;

EventDispatcher::EventDispatcher()
{
    //handlers_ = std::vector<EventHandler *>();
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
    handlers_.push_back(handler);
}

void EventDispatcher::sendEvent(Event * event)
{
    //for(std::vector<EventHandler *>::iterator iterator = handlers_.begin(); iterator != handlers_.end(); ++iterator) {
    for(std::list<EventHandler *>::iterator iterator = handlers_.begin(); iterator != handlers_.end(); ++iterator) {
        (*iterator)->handleEvent(event);
    }
}
