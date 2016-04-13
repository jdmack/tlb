#include "action/action.h"
#include "action/deadAction.h"

DeadAction::DeadAction()
{
    type_ = ACTION_DEAD;
}

bool DeadAction::update(Entity * entity, int deltaTicks)
{
    return true;
}
