#include "aiState/AIState.h"
#include "action/Action.h"

AIState::AIState()
{
    entity_ = nullptr;
    stateMachine_ = nullptr;
    type_ = STATE_IDLE;
}

AIState::~AIState()
{

}

bool AIState::update(int deltaTicks)
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

ActionType AIState::actionType()
{
    return ACTION_IDLE;
}
