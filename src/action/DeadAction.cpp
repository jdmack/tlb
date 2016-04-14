#include "action/Action.h"
#include "action/DeadAction.h"

DeadAction::DeadAction()
{
    type_ = ACTION_DEAD;
}

bool DeadAction::update(Entity * entity, int deltaTicks)
{
    return true;
}
