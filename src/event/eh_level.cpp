#include "event/eh_level.h"
EHLevel::EHLevel()
{

}

EHLevel::~EHLevel()
{

}

void EHLevel::handle_event(Event event)
{
    switch (event.type()) {
        case EVENT_MOUSE_RCLICK:
            break;

        case EVENT_MOUSE_LCLICK:
            break;

    }
}
