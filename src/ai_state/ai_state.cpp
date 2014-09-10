#include "ai_state/ai_state.h"
#include "action/action.h"

AIState::AIState()
{

}

AIState::~AIState()
{

}

bool AIState::update(Entity * entity, int delta_ticks)
{
    return true;
}

void AIState::stop()
{

}

void AIState::start()
{

}

void AIState::end()
{
}

ActionType AIState::action_type()
{
    return ACTION_IDLE;
}
