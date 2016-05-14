#include "event/EventHandler.h"

int EventHandler::idCounter_ = 1;

EventHandler::EventHandler()
{
    id_ = idCounter_++; 
}

EventHandler::~EventHandler()
{

}

bool EventHandler::handleEvent(Event * event)
{
    return true;
}
