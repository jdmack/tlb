#include "action/Action.h"
#include "action/IdleAction.h"

IdleAction::IdleAction()
{
    type_ = ACTION_IDLE;
}

bool IdleAction::update(Entity * entity, int deltaTicks)
{
    return true;
}
