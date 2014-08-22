#include "actions/action.h"
#include "actions/dead_action.h"

DeadAction::DeadAction()
{
    type_ = ACTION_DEAD;
}

bool DeadAction::update(Entity * entity, int delta_ticks)
{
    return true;
}
