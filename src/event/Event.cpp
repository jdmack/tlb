#include "event/Event.h"

Event::Event()
{
    type_ = EVENT_BLANK;
}

Event::Event(EventType type)
{
    type_ = type;
}

Event::~Event()
{

}
