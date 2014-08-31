#include "action/action.h"
#include "action/idle_action.h"

IdleAction::IdleAction()
{
    type_ = ACTION_IDLE;
}

bool IdleAction::update(Entity * entity, int delta_ticks)
{
    return true;
}
