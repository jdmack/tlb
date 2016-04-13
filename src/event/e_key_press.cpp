#include "event/eKeyPress.h"
#include "event/event.h"

EKeyPress::EKeyPress()
{
    type_ = EVENT_KEY_PRESS;
    keyType_ = KEY_NONE;
}

EKeyPress::EKeyPress(KeyType keyType)
{
    type_ = EVENT_KEY_PRESS;
    keyType_ = keyType;
}

EKeyPress::~EKeyPress()
{

}
