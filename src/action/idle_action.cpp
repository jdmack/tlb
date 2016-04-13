#include "action/action.h"
#include "action/idleAction.h"

IdleAction::IdleAction()
{
    type_ = ACTION_IDLE;
}

bool IdleAction::update(Entity * entity, int deltaTicks)
{
    return true;
}
