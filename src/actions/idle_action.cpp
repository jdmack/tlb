#include "actions/action.h"
#include "actions/idle_action.h"

IdleAction::IdleAction()
{
    type_ = ACTION_IDLE;
}

bool IdleAction::update(Entity * entity, int delta_ticks)
{
    return true;
}
