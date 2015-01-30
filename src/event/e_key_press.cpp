#include "event/e_key_press.h"
#include "event/event.h"

EKeyPress::EKeyPress()
{
    type_ = EVENT_KEY_PRESS;
    key_type_ = KEY_NONE;
}

EKeyPress::EKeyPress(KeyType key_type)
{
    type_ = EVENT_KEY_PRESS;
    key_type_ = key_type;
}

EKeyPress::~EKeyPress()
{

}
