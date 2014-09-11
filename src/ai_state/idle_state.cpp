#include "ai_state/idle_state.h"
#include "ai_state/ai_state.h"
#include "action/action.h"

IdleState::IdleState()
{
}

IdleState::~IdleState()
{

}

bool IdleState::update(Entity * entity, int delta_ticks)
{

    return true;
}

void IdleState::stop()
{

}

ActionType IdleState::action_type()
{
    return ACTION_IDLE;
}
