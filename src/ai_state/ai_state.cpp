#include "ai_state/ai_state.h"
#include "action/action.h"

AIState::AIState()
{
    entity_ = nullptr;
    state_machine_ = nullptr;
    type_ = STATE_IDLE;
}

AIState::~AIState()
{

}

bool AIState::update(int delta_ticks)
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
